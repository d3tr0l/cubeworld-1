/*
 * Copyright 2012 Scott MacDonald
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <common/time.h>
#include <common/assert.h>
#include <ostream>

const double Time::TimeDelta = 0.000001;

/**
 * Default time constructor which will set the time to zero.
 */
Time::Time()
    : mSeconds( 0.0 )
{
}

/**
 * Copy constructor
 */
Time::Time( const Time& t )
    : mSeconds( t.mSeconds )
{
}

/**
 * Value constructor
 */
Time::Time( unsigned int seconds )
    : mSeconds( static_cast<double>(seconds) )
{
}

/**
 * Constructor
 */
Time::Time( float seconds )
    : mSeconds( static_cast<double>(seconds) )
{
    ASSERT_MSG( seconds >= -TimeDelta, "Time must be positive" );
}

/**
 * Constructor
 */
Time::Time( double seconds )
    : mSeconds( seconds )
{
    ASSERT_MSG( seconds >= -TimeDelta, "Time must be positive" );
}

/**
 * Assignment operator
 */
Time& Time::operator = ( const Time& rhs )
{
    mSeconds = rhs.mSeconds;
    return *this;
}

/**
 * Equality operator
 */
bool Time::operator == ( const Time& rhs ) const
{
    return ( mSeconds + TimeDelta >= rhs.mSeconds &&
             mSeconds - TimeDelta <= rhs.mSeconds );
}

/**
 * Inequality operator
 */
bool Time::operator != ( const Time& rhs ) const
{
    return !( *this == rhs );
}

/**
 * Less than operator
 */
bool Time::operator < ( const Time& rhs ) const
{
    return mSeconds < ( rhs.mSeconds - TimeDelta );
}

/**
 * Less than equals operator
 */
bool Time::operator <= ( const Time& rhs ) const
{
    return mSeconds <= ( rhs.mSeconds + TimeDelta );
}

/**
 * Greater than operator
 */
bool Time::operator > ( const Time& rhs ) const
{
    return mSeconds > ( rhs.mSeconds + TimeDelta );
}

/**
 * Greater than equals operator
 */
bool Time::operator >= ( const Time& rhs ) const
{
    return mSeconds >= ( rhs.mSeconds - TimeDelta );
}

/**
 * Addition operator
 */
Time Time::operator + ( const Time& rhs ) const
{
    return Time( mSeconds + rhs.mSeconds );
}

/**
 * Self addition operator
 */
Time& Time::operator += ( const Time& rhs )
{
    mSeconds += rhs.mSeconds;
    return *this;
}

/**
 * Subtraction operator
 */
Time Time::operator - ( const Time& rhs ) const
{
    ASSERT_MSG( mSeconds >= rhs.mSeconds, "Subtraction cannot result in negative" );
    return Time( mSeconds - rhs.mSeconds );
}

/**
 * Self subtraction operator
 */
Time& Time::operator -= ( const Time& rhs )
{
    ASSERT_MSG( mSeconds >= rhs.mSeconds, "Subtraction cannot result in negative" );
    
    mSeconds -= rhs.mSeconds;
    return *this;
}

/**
 * Return the internal time representation. This is the internal value for
 * this instance. Use minutes() and seconds() generally
 */
double Time::toDouble() const
{
    return mSeconds;
}

/**
 * Return the number of hours that have passed
 */
unsigned int Time::hours() const
{
    return static_cast<unsigned int>( mSeconds / 3600.0 );
}

/**
 * Return the number of minutes that have elapsed for this time object
 */
unsigned int Time::minutes() const
{
    return static_cast<unsigned int>( mSeconds / 60.0 );
}

/**
 * Return the number of seconds that have elpased for this time object
 */
unsigned int Time::seconds() const
{
    return static_cast<unsigned int>( mSeconds );
}

/**
 * Return the number of milliseconds that have elapsed for this time
 * object
 */
unsigned long long Time::milliseconds() const
{
    return static_cast<unsigned long long>( mSeconds * 1000.0 );
}

/**
 * Return the number of microseconds that have elpased for this time
 * object
 */
unsigned long long Time::microseconds() const
{
    return static_cast<unsigned long long>( mSeconds * 1000000.0 );
}

/**
 * Convert microseconds to time object
 */
Time Time::fromMicroSeconds( unsigned int microsecs )
{
    return Time( static_cast<double>(microsecs) / 1000000.0 );
}

/**
 * Convert milliseconds to a time object
 */
Time Time::fromMilliSeconds( unsigned int ms )
{
    return Time( static_cast<double>(ms) / 1000.0 );
}

/**
 * Stream out operator
 */
std::ostream& operator << ( std::ostream& os, const Time& t )
{
    os << t.toDouble() << std::endl;
    return os;
}
