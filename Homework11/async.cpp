#include "async.h"

std::map<async::handle_t ,std::shared_ptr<Context>> MapContext;

namespace async {

    handle_t connect(std::size_t bulk) {
        auto h = std::make_shared<Context>(bulk);
        MapContext.emplace(std::make_pair(h.get(),h));
        return h.get();
    }

    void receive(handle_t handle, const char *data, std::size_t size) {
        MapContext[handle]->Receive(data,size);
    }

    void disconnect(handle_t handle)
    {
        MapContext[handle]->Stop();
    }

}