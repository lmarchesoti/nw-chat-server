#include "log.h"

#include <string>
#include <mutex>
#include <condition_variable>
#include <fstream>
#include <memory>
#include <thread>

std::shared_ptr<Log> Log::get() {

	static auto instance = std::make_shared<Log>();

	instance->start();

	return instance;

}

void Log::log_this(std::string s) {

	std::lock_guard<std::mutex> lock(this->queue_mutex);

	this->log_queue.push(s);
	this->queue_cv.notify_one();
}

void Log::consume_messages() {

	while(true) {

		{
			std::unique_lock<std::mutex> lock(this->queue_mutex);

			this->queue_cv.wait(lock, [=]{return this->log_queue.size() > 0;});

			std::ofstream logfile("log.txt", std::ios_base::app);
			logfile << this->log_queue.front() << std::endl;
			this->log_queue.pop();

		}
	}
}

void Log::start() {

	if (this->logging == false) {

		this->logging = true;
		std::thread t(&Log::consume_messages, std::ref(*(Log::get())));
		t.detach();
	}
}
