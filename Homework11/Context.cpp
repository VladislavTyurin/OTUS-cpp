#include "Context.h"

Context::Context(const int bulk_size)
{
    t = std::thread( [this, bulk_size]()
    {
        string_handler.reset( new StringHandler( bulk_size ) ); 
        this->Waiting();
    } );
}

Context::~Context()
{
    if(t.joinable())
         t.join();
}

void Context::Receive(const char *data, size_t size)
{ 
    ParseData( data, size );
    cv.notify_one();
}

void Context::Stop()
{
    HandleRest();
    done = true;
    cv.notify_one();
}

void Context::Waiting()
{
    while(!done) 
    {
        std::unique_lock<std::mutex> lk(cv_m);
        if(done)
        {
            string_handler->Stop();
            lk.unlock();
            break;
        }
        cv.wait(lk);
        if( !deque_data.empty() )
        {
            auto bulk = deque_data.front();
            deque_data.pop_front();
            string_handler->ReadCommand( bulk );
        }
        lk.unlock();
    }
}

void Context::ParseData( const char* data, size_t len )
{
    std::string command = data;
    std::string word = "";
    for(int i = 0;i<len;++i)
    {
        if(data[i]=='\n')
        {
            std::lock_guard<std::mutex> lk( cv_m );
            if(!word.empty())
                deque_data.emplace_back( word );
            word.clear();
            continue;
        }
        word+=data[i];
    }
    if(data[len-1]!='\n' && !word.empty())
        deque_data.emplace_back( word );
}

void Context::HandleRest()
{
    while( !QE )
    {
        cv.notify_one();
        QE = GetQE();
    }
}

bool Context::GetQE()
{
    std::lock_guard<std::mutex> lc( cv_m );
    return deque_data.empty();
}
