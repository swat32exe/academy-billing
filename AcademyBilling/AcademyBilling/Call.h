#pragma once
#include <string>
#include <time.h>

namespace AcademyBilling
{
	class Call
	{
	private:
		std::string from;
		std::string to;
		time_t time;
		unsigned int duration;
	public:
		Call(void);
		Call(const std::string& From,const std::string& To,const time_t& Time,const unsigned int& Duration);
		~Call(void);
		std::string getFrom() const;
		void setFrom(const std::string&);
		std::string getTo() const;
		void setTo(const std::string&);
		time_t getTime() const;
		void setTime(const time_t&);
		unsigned int getDuration() const;
		void setDuration(const unsigned int&);
	};
}
