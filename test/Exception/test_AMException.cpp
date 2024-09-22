#include "../../AMException.h"
#include "gtest/gtest.h"

using namespace std;
using namespace AMCore;

const constexpr char* g_strings[][2] = {
    {
        "simple",
        "Simple"
    },
    {
        "enhanced",
        "Enhanced"
    },
    {
        "toplevel",
        "Top-Level"
    },
};

TEST(AMException, BasicTest)
{
    AMLString se0 = _(g_strings[0][0]);
    AMLString se1 = _(g_strings[1][0]);
    AMLString se2 = _(g_strings[2][0]);

    _T_AM_StringList* list = _T_AM_StringList::GetStringTable("default");
    EXPECT_NE(list, nullptr);
    _T_AM_StringItemBase* p = list->_M_first_item;
    EXPECT_NE(p, nullptr);
    p = p->_M_next; // skip empty string
    p->setTranslatedString(g_strings[1][1]); // Enhanced is first
    p = p->_M_next;
    p->setTranslatedString(g_strings[0][1]);
    p = p->_M_next;
    p->setTranslatedString(g_strings[2][1]);

    try
    {
        throw AMException(_(g_strings[0][0]));
        FAIL() << "This line must not be reached since an exception is thrown";
    }
    catch(AMException e)
    {
        EXPECT_STREQ(g_strings[0][1], e.what() );
    }
    catch (...)
    {
        FAIL() << "Unexpected exception";
    }
}

TEST(AMException, CascadedTest)
{
    try
    {
        try
        {
            try
            {
                throw AMException(_(g_strings[0][0]));
                FAIL() << "This line must not be reached since an exception is thrown";
            }
            catch(AMException e)
            {
                EXPECT_STREQ(g_strings[0][1], e.what() );
                throw AMException(_(g_strings[1][0]), e);
                FAIL() << "This line must not be reached since an exception is thrown";
            }
            catch (...)
            {
                FAIL() << "Unexpected exception";
            }
        }
        catch(AMException e)
        {
            EXPECT_STREQ(e.what(), g_strings[1][1]);
            const std::list<AMException>& trace = e.get_trace();
            std::list<AMException>::const_iterator i = trace.begin();
            EXPECT_NE(trace.end(), i);
            EXPECT_STREQ(g_strings[0][1], i->what());
            throw AMException(_(g_strings[2][0]), e);
            FAIL() << "This line must not be reached since an exception is thrown";
        }
        catch (...)
        {
            FAIL() << "Unexpected exception";
        }
    }
    catch(AMException e)
    {
        EXPECT_STREQ(e.what(), g_strings[2][1]);
        const std::list<AMException>& trace = e.get_trace();
        std::list<AMException>::const_iterator i = trace.begin();
        EXPECT_NE(trace.end(), i);
        EXPECT_STREQ(g_strings[0][1], i->what());
        ++i;
        EXPECT_NE(trace.end(), i);
        EXPECT_STREQ(g_strings[1][1], i->what());
    }
    catch (...)
    {
        FAIL() << "Unexpected exception";
    }
}

int main(int argc, char **argv)
{
     ::testing::InitGoogleTest(&argc, argv);
     return RUN_ALL_TESTS();
}
