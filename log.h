#ifndef _LOG_H_
#define _LOG_H_

#include <string>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <memory>
#include <atomic>

class Log {

public:
	Log() : logging(false) { };
	void log_this(std::string);
	static std::shared_ptr<Log> get();
	void start();

private:
	void consume_messages();
	std::mutex queue_mutex;
	std::condition_variable queue_cv;
	std::queue<std::string> log_queue;
	std::atomic<bool> logging;
	
};

#endif
