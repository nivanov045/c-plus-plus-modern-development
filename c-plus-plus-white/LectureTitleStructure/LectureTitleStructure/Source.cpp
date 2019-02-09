#include <string>

struct Specialization
{
	std::string value;
	explicit Specialization(std::string iValue) : value(iValue)
	{
	}
};

struct Course
{
	std::string value;
	explicit Course(std::string iValue) : value(iValue)
	{
	}
};

struct Week
{
	std::string value;
	explicit Week(std::string iValue) : value(iValue)
	{
	}
};

struct LectureTitle {
	std::string specialization;
	std::string course;
	std::string week;
	
	LectureTitle(Specialization iSpecialization, Course iCourse, Week iWeek) :
	specialization(iSpecialization.value), course(iCourse.value), week(iWeek.value)
	{
	}
};