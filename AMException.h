/**
 * @file: AMException.h
 * Cascaded exception with localization.
 *
 * @author Robotea technologies s.r.o.
 */

#ifndef __AMEXCEPTION_H__
#define __AMEXCEPTION_H__

#include "amlstring/AMLString.h"

#include <list>

namespace AMCore {
    /**
     *  @class AMException
     *  @brief Base class for AMCore exceptions.
     *
     *  @ingroup exceptions
     *
     */
    class AMException: public std::exception
    {
    public:
/*
        AMException(const char* what):
            std::exception(),
            msg_(_T_AM_String::getTextImpl([=](){ return what;}))
        {
        }
*/
        /**
         *  @brief AMException default constructor.
         *  @throw This function will not throw an exception.
         */
        AMException() noexcept :
            std::exception(),
            msg_(_(""))
        {
        }

        /**
         *  @brief AMException constructor with AMLString parameter.
         *  @param what const reference to multilanguage string.
         *  @throw This function will not throw an exception.
         */
        AMException(const AMLString& what) noexcept :
            std::exception(),
            msg_(what)
        {
        }

        /**
         *  @brief AMException constructor with AMLString and previous AMException parameters.
         *  @param what const reference to multilanguage string.
         *  @param prev reference to previous exception object. Its content is moved to the list of previous exceptions.
         *  @throw This function will not throw an exception.
         */
        AMException(const AMLString& what, AMException& prev) noexcept :
            std::exception(),
            msg_(what)
        {
            prev_list_.swap(prev.prev_list_);
            prev_list_.push_back(prev);
        }

        /**
         *  @brief what
         *  @returns const string with description. Size of this string is not limited.
         *  @throw This function will not throw an exception.
         */
        const char* what() const noexcept { return msg_.c_str(); }

	/**
         *  @brief get_trace
         *  @returns const reference to the list of previous exceptions.
         *  @throw This function will not throw an exception.
         */
        const std::list<AMException>& get_trace() const noexcept { return prev_list_; }

    protected:
        AMLString msg_;
    private:
        std::list<AMException> prev_list_;
    };


} // namespace AMCore

#endif
