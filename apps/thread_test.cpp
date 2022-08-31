#include <condition_variable>
#include <thread>
#include <mutex>
#include <csignal>
#include <iostream>

static std::mutex m;
static bool stop = false;

static std::condition_variable c;

static void sigint_handler(int)
{
    {
        std::lock_guard<std::mutex> lk(m);
        stop = true;
    }
    c.notify_one();
}

static void logger()
{
    while (!stop)
    {
        std::cout << "Waiting...\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

int main()
{
    signal(SIGINT, sigint_handler);

    std::thread t(logger);

    std::unique_lock<std::mutex> lk(m);
    c.wait_for(lk, std::chrono::milliseconds(500), [] { return stop; });

    t.join();

    return EXIT_SUCCESS;
}

