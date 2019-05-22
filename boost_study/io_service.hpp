//
// Created by firesWu on 2019-05-22.
//

#ifndef BOOST_STUDY_IO_SERVICE_HPP
#define BOOST_STUDY_IO_SERVICE_HPP

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/bind.hpp>
#include <iostream>

boost::mutex global_stream_lock;

void WorkerThread( boost::shared_ptr< boost::asio::io_service > io_service )
{
    global_stream_lock.lock();
    std::cout << "[" << boost::this_thread::get_id()
              << "] Thread Start" << std::endl;
    global_stream_lock.unlock();

    io_service->run();

    global_stream_lock.lock();
    std::cout << "[" << boost::this_thread::get_id()
              << "] Thread Finish" << std::endl;
    global_stream_lock.unlock();
}

size_t fib( size_t n )
{
    if ( n <= 1 )
    {
        return n;
    }
    boost::this_thread::sleep(
            boost::posix_time::milliseconds( 1000 )
    );
    return fib( n - 1 ) + fib( n - 2);
}

void CalculateFib( size_t n )
{
    global_stream_lock.lock();
    std::cout << "[" << boost::this_thread::get_id()
              << "] Now calculating fib( " << n << " ) " << std::endl;
    global_stream_lock.unlock();

    size_t f = fib( n );

    global_stream_lock.lock();
    std::cout << "[" << boost::this_thread::get_id()
              << "] fib( " << n << " ) = " << f << std::endl;
    global_stream_lock.unlock();
}

int ios_service_test()
{
    boost::shared_ptr< boost::asio::io_service > io_service(
            new boost::asio::io_service
    );
    boost::shared_ptr< boost::asio::io_service::work > work(
            new boost::asio::io_service::work( *io_service )
    );

    global_stream_lock.lock();
    std::cout << "[" << boost::this_thread::get_id()
              << "] The program will exit when all work has finished."
              << std::endl;
    global_stream_lock.unlock();

    boost::thread_group worker_threads;
    for( int x = 0; x < 1; ++x )
    {
        worker_threads.create_thread(
                boost::bind( &WorkerThread, io_service )
        );
    }

    io_service->post( boost::bind( CalculateFib, 3 ) );
    io_service->post( boost::bind( CalculateFib, 4 ) );
    io_service->post( boost::bind( CalculateFib, 5 ) );

    work.reset();

    worker_threads.join_all();
    std::cout<<"end"<<std::endl;
    return 0;
}

#endif //BOOST_STUDY_IO_SERVICE_HPP
