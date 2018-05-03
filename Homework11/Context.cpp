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
    ParseData( data );
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

void Context::ParseData( const char* data )
{
    std::string command = data;
    std::string word = "";
    for( auto it = command.begin(); it != command.end(); ++it )
    {
        if( *it == '\n' )
        {
            std::lock_guard<std::mutex> lk( cv_m );
            deque_data.emplace_back( word );
            word.clear();
            continue;
        }
        word += *it;
    }
    if( *std::prev( command.end() )!='\n' )
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
