# AMException - cascaded exception with localization.

Typical error is cascaded. Let's imagine that you have application for editing documents. Than, you may want present IO error to user if occured. For example:

- Unable save document
- *Because*
- Unable write file
- *Because*
- Disk is full

## Usage

Let's have this table. First word is an original string, second is a "translated" string.

    #include "amexception/AMException.h"

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

## Documetation

There are doxygen generated documentation [here on libandromeda.org](http://libandromeda.org/AMException/latest/).

## Building AMException

### Getting sources

```bash
git submodule update
```

### Compiling

```bash

mkdir cmake-build-debug

cd cmake-build-debug

cmake ..

make
```

### Single test (not necessary)

```bash
./TEST_AMExeption
```

## Licencing

This library is under GNU GPL v3 licence. If you need business licence, don't hesitate to contact [me](mailto:zdenek.skulinek\@robotea.com?subject=Licence+for+AMException).

## Contribute

Please contact [me](mailto:zdenek.skulinek\@robotea.com?subject=Licence for AMException).

## Dependencies

1. [Google test](https://github.com/google/googletest.git)
2. [AMLString](https://github.com/robotea/amlstring.git)