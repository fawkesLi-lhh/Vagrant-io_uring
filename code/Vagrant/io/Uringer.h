#ifndef _URINGER_H_
#define _URINGER_H_

#include <liburing.h>
#include <mutex> 
#include <functional>
#include <map>

typedef long long ll;

class Uringer{
public:
    void init(int len);
    void submit();
    void addPoll(int fd,unsigned int poll_mask,::std::function<void()> fun);
    void addRead(int fd,void *buffer,unsigned int len,off_t offset,::std::function<void()> fun);
    void addWriteV(int fd,const iovec* iovecs,unsigned int nr_vecs,off_t offset,::std::function<void()> fun);
    struct io_uring_cqe* wait_cqe();
    struct io_uring_cqe* peek_cqe();
    void cqe_seen(struct io_uring_cqe* cqe);
    void finishEvent(ll id);
private:
    struct io_uring ring;
    ::std::mutex mtx;
    ::std::map<ll,::std::function<void()>> mp;
    ll idCount;
};




#endif 