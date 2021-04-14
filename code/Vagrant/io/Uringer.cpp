#include "Uringer.h"

#include<assert.h>

void Uringer::init(int len){
    std::unique_lock<std::mutex> locker(mtx);
    int ret = io_uring_queue_init(len,&ring,0);
    assert(ret>=0);
    idCount = 0;
}

void Uringer::submit(){
    std::unique_lock<std::mutex> locker(mtx);
    io_uring_submit(&ring);
}

void Uringer::addPoll(int fd,unsigned int poll_mask,::std::function<void()> fun){
    std::unique_lock<std::mutex> locker(mtx);
    mp[++idCount] = fun;
    struct io_uring_sqe *sqe = io_uring_get_sqe(&ring);
    io_uring_prep_poll_add(sqe,fd,poll_mask);
    sqe->user_data = idCount;
}

void Uringer::addRead(int fd,void *buffer,unsigned int len,off_t offset,::std::function<void()> fun){
    std::unique_lock<std::mutex> locker(mtx);
    mp[++idCount] = fun;
    struct io_uring_sqe *sqe = io_uring_get_sqe(&ring);
    io_uring_prep_read(sqe,fd,buffer,len,offset);
    sqe->user_data = idCount;
}

void Uringer::addWriteV(int fd,const iovec* iovecs,unsigned int nr_vecs,off_t offset,::std::function<void()> fun){
    std::unique_lock<std::mutex> locker(mtx);
    mp[++idCount] = fun;
    struct io_uring_sqe *sqe = io_uring_get_sqe(&ring);
    io_uring_prep_writev(sqe,fd,iovecs,nr_vecs,offset);
    sqe->user_data = idCount;
}

struct io_uring_cqe* Uringer::wait_cqe(){
    std::unique_lock<std::mutex> locker(mtx);
    struct io_uring_cqe* cqe;
    io_uring_wait_cqe(&ring,&cqe);
    return cqe;
}
struct io_uring_cqe* Uringer::peek_cqe(){
    std::unique_lock<std::mutex> locker(mtx);
    struct io_uring_cqe* cqe = nullptr;
    int flag = io_uring_peek_cqe(&ring,&cqe);
    return flag == 0? cqe:nullptr;
}

void Uringer::cqe_seen(struct io_uring_cqe* cqe){
    std::unique_lock<std::mutex> locker(mtx);
    io_uring_cqe_seen(&ring, cqe);
}

void Uringer::finishEvent(ll id){
    mp[id]();
    std::unique_lock<std::mutex> locker(mtx);
    mp.erase(mp.find(id));
}
