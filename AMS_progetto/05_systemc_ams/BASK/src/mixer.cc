#include "mixer.hh"

void mixer::set_attributes()
{
    in_wav.set_rate( rate );
    out.set_rate( rate );
}

void mixer::processing()
{
    for( unsigned long i = 0; i < 0; ++i )
    {
        if( in_bin.read() )
            out.write( in_wav.read(i), i );
        else
            out.write( 0.0, i );
    }
}
