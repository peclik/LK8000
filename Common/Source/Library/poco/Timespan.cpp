//
// Timespan.cpp
//
// $Id: //poco/1.4/Foundation/src/Timespan.cpp#1 $
//
// Library: Foundation
// Package: DateTime
// Module:  Timespan
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
//
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//


#include "Poco/Timespan.h"
#include <algorithm>


namespace Poco {


const Timespan::TimeDiff Timespan::MILLISECONDS = 1000;
const Timespan::TimeDiff Timespan::SECONDS      = 1000*Timespan::MILLISECONDS;
const Timespan::TimeDiff Timespan::MINUTES      =   60*Timespan::SECONDS;
const Timespan::TimeDiff Timespan::HOURS        =   60*Timespan::MINUTES;
const Timespan::TimeDiff Timespan::DAYS         =   24*Timespan::HOURS;


Timespan::Timespan():
	_span(0)
{
}


Timespan::Timespan(TimeDiff microseconds):
	_span(microseconds)
{
}


Timespan::Timespan(long seconds, long microseconds):
	_span(TimeDiff(seconds)*SECONDS + microseconds)
{
}


Timespan::Timespan(int days, int hours, int minutes, int seconds, int microseconds):
	_span(TimeDiff(microseconds) + TimeDiff(seconds)*SECONDS + TimeDiff(minutes)*MINUTES + TimeDiff(hours)*HOURS + TimeDiff(days)*DAYS)
{
}


Timespan::Timespan(const Timespan& timespan):
	_span(timespan._span)
{
}


Timespan::~Timespan()
{
}


Timespan& Timespan::operator = (const Timespan& timespan)
{
	_span = timespan._span;
	return *this;
}


Timespan& Timespan::operator = (TimeDiff microseconds)
{
	_span = microseconds;
	return *this;
}


Timespan& Timespan::assign(int days, int hours, int minutes, int seconds, int microseconds)
{
	_span = TimeDiff(microseconds) + TimeDiff(seconds)*SECONDS + TimeDiff(minutes)*MINUTES + TimeDiff(hours)*HOURS + TimeDiff(days)*DAYS;
	return *this;
}


Timespan& Timespan::assign(long seconds, long microseconds)
{
	_span = TimeDiff(seconds)*SECONDS + TimeDiff(microseconds);
	return *this;
}


void Timespan::swap(Timespan& timespan)
{
	std::swap(_span, timespan._span);
}


Timespan Timespan::operator + (const Timespan& d) const
{
	return Timespan(_span + d._span);
}


Timespan Timespan::operator - (const Timespan& d) const
{
	return Timespan(_span - d._span);
}


Timespan& Timespan::operator += (const Timespan& d)
{
	_span += d._span;
	return *this;
}


Timespan& Timespan::operator -= (const Timespan& d)
{
	_span -= d._span;
	return *this;
}


Timespan Timespan::operator + (TimeDiff microseconds) const
{
	return Timespan(_span + microseconds);
}


Timespan Timespan::operator - (TimeDiff microseconds) const
{
	return Timespan(_span - microseconds);
}


Timespan& Timespan::operator += (TimeDiff microseconds)
{
	_span += microseconds;
	return *this;
}


Timespan& Timespan::operator -= (TimeDiff microseconds)
{
	_span -= microseconds;
	return *this;
}


} // namespace Poco
