#ifndef _gg_thread_pool_h_
#define _gg_thread_pool_h_

// include files

#include "gg/core/pattern/non_copyable.h"
#include "gg/core/type/type.h"

// namespace

namespace gg
{
    // class in charge of define a thread pool

    class thread_pool final : public non_copyable
    {
    public:

        // constructors

        thread_pool(void) noexcept;
        ~thread_pool(void) noexcept = default;

    private:

        // uint32 m_max_queue_size;
        // uint32 m_num_threads;
        // uint32 m_queue_size;

        // bool8 m_queue_closed : 1;
        // bool8 m_shutdown : 1;

        // Work *mpQueueHead;
        // Work *mpQueueTail;
        // thread * m_threads;

        // pthread_mutex_t mQueueLock;
        // pthread_cond_t mQueueEmpty;
        // pthread_cond_t mQueueNotEmpty;
        // pthread_cond_t mQueueNotFull;
    };
}

#endif // _gg_thread_pool_h_
