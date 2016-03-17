/*
 * param.cc
 *
 *  Created on: Jan 14, 2014
 *      Author: nsoblath
 */

#define SCARAB_API_EXPORTS

#include <sstream>
using std::string;
using std::stringstream;

#include "param.hh"

//#include "logger.hh"


namespace scarab
{
    //LOGGER( dlog, "param" );

    SCARAB_API unsigned param::s_indent_level = 0;

    param::param()
    {
    }

    param::param( const param& )
    {
    }

    param::~param()
    {
    }

    bool param::has_subset( const param& /*a_subset*/ ) const
    {
        // this version of has_subset should only ever be called if a_subset is a null param (i.e. not one of the derived classes)
        return true;
    }

    //************************************
    //***********  VALUE  ****************
    //************************************

    param_value::param_value() :
            param(),
            f_value_type( k_invalid ),
            f_buffer()
    {
        //WARN( dlog, "param_value constructor: k_invalid" );
    }

    param_value::param_value( bool a_value ) :
            param(),
            f_value_type( k_bool ),
            f_buffer()
    {
        f_value.f_bool = a_value;
        //WARN( dlog, "param_value constructor: bool --> bool" );
    }

    param_value::param_value( uint8_t a_value ) :
            param(),
            f_value_type( k_uint ),
            f_buffer()
    {
        f_value.f_uint = a_value;
        //WARN( dlog, "param_value constructor: uint8 --> uint" );
    }

    param_value::param_value( uint16_t a_value ) :
            param(),
            f_value_type( k_uint ),
            f_buffer()
    {
        f_value.f_uint = a_value;
        //WARN( dlog, "param_value constructor: uint16 --> uint" );
    }

    param_value::param_value( uint32_t a_value ) :
            param(),
            f_value_type( k_uint ),
            f_buffer()
    {
        f_value.f_uint = a_value;
        //WARN( dlog, "param_value constructor: uint32 --> uint" );
    }

    param_value::param_value( uint64_t a_value ) :
            param(),
            f_value_type( k_uint ),
            f_buffer()
    {
        f_value.f_uint = a_value;
        //WARN( dlog, "param_value constructor: uint64 --> uint" );
    }

    param_value::param_value( int8_t a_value ) :
            param(),
            f_value_type( k_int ),
            f_buffer()
    {
        f_value.f_int = a_value;
        //WARN( dlog, "param_value constructor: int8 --> int" );
    }

    param_value::param_value( int16_t a_value ) :
            param(),
            f_value_type( k_int ),
            f_buffer()
    {
        f_value.f_int = a_value;
        //WARN( dlog, "param_value constructor: int16 --> int" );
    }


    param_value::param_value( int32_t a_value ) :
            param(),
            f_value_type( k_int ),
            f_buffer()
    {
        f_value.f_int = a_value;
        //WARN( dlog, "param_value constructor: int32 --> int" );
    }

    param_value::param_value( int64_t a_value ) :
            param(),
            f_value_type( k_int ),
            f_buffer()
    {
        f_value.f_int = a_value;
        //WARN( dlog, "param_value constructor: int64 --> int" );
    }

    param_value::param_value( float a_value ) :
            param(),
            f_value_type( k_double ),
            f_buffer()
    {
        f_value.f_double = a_value;
        //WARN( dlog, "param_value constructor: float --> double" );
    }

    param_value::param_value( double a_value ) :
            param(),
            f_value_type( k_double ),
            f_buffer()
    {
        f_value.f_double = a_value;
        //WARN( dlog, "param_value constructor: double --> double" );
    }

    param_value::param_value( const char* a_value ) :
            param(),
            f_value_type( k_string ),
            f_buffer()
    {
        f_value.f_string = new string( a_value );
        //WARN( dlog, "param_value constructor: char* --> k_string" );
    }

    param_value::param_value( const string& a_value ) :
            param(),
            f_value_type( k_string ),
            f_buffer()
    {
        f_value.f_string = new string( a_value );
        //WARN( dlog, "param_value constructor: string --> k_string" );
    }

    param_value::param_value( const param_value& orig ) :
            param( orig ),
            f_value( orig.f_value ),
            f_value_type( orig.f_value_type ),
            f_buffer()
    {
        if( f_value_type == k_string )
        {
            f_value.f_string = new string( *orig.f_value.f_string );
        }
        //WARN( dlog, "param_value copy constructor: " << type() );
    }

    param_value::~param_value()
    {
        if( f_value_type == k_string )
        {
            delete f_value.f_string;
        }
    }

    param_value& param_value::operator=( const param_value& rhs )
    {
        if( &rhs == this ) return *this;

        if( f_value_type == k_string )
        {
            delete f_value.f_string;
        }

        if( rhs.f_value_type == k_string )
        {
            f_value.f_string = new string( *rhs.f_value.f_string );
        }
        else
        {
            f_value = rhs.f_value;
        }
        f_value_type = rhs.f_value_type;

        return *this;
    }

    std::string param_value::type() const
    {
        switch( f_value_type )
        {
            case k_invalid:
                return string( "invalid" );
                break;
            case k_bool:
                return string( "bool" );
                break;
            case k_uint:
                return string( "uint" );
                break;
            case k_int:
                return string( "int" );
               break;
            case k_double:
                return string( "double" );
                break;
            case k_string:
                return string( "string" );
                break;
        }
        return string( "unknown" );
    }

    bool param_value::as_bool() const
    {
        if( f_value_type == k_bool ) return f_value.f_bool;
        else if( f_value_type == k_uint ) return f_value.f_uint != 0;
        else if( f_value_type == k_int ) return f_value.f_int != 0;
        else if( f_value_type == k_double ) return f_value.f_double != 0.;
        else if( f_value_type == k_string )
        {
            return ! f_value.f_string->empty();
        }
        return false;
    }

    uint64_t param_value::as_uint() const
    {
        if( f_value_type == k_bool ) return (uint64_t)f_value.f_bool;
        else if( f_value_type == k_uint ) return f_value.f_uint;
        else if( f_value_type == k_int ) return (uint64_t)f_value.f_int;
        else if( f_value_type == k_double ) return (uint64_t)f_value.f_double;
        else if( f_value_type == k_string )
        {
            std::stringstream t_conv;
            t_conv << k_string;
            uint64_t t_return;
            t_conv >> t_return;
            return t_return;
        }
        return 0.;
    }
    int64_t param_value::as_int() const
    {
        if( f_value_type == k_bool ) return (int64_t)f_value.f_bool;
        else if( f_value_type == k_uint ) return (int64_t)f_value.f_uint;
        else if( f_value_type == k_int ) return f_value.f_int;
        else if( f_value_type == k_double ) return (int64_t)f_value.f_double;
        else if( f_value_type == k_string )
        {
            std::stringstream t_conv;
            t_conv << k_string;
            int64_t t_return;
            t_conv >> t_return;
            return t_return;
        }
        return 0.;
    }
    double param_value::as_double() const
    {
        if( f_value_type == k_bool ) return f_value.f_bool;
        else if( f_value_type == k_uint ) return (double)f_value.f_uint;
        else if( f_value_type == k_int ) return (double)f_value.f_int;
        else if( f_value_type == k_double ) return f_value.f_double;
        else if( f_value_type == k_string )
        {
            std::stringstream t_conv;
            t_conv << k_string;
            double t_return;
            t_conv >> t_return;
            return t_return;
        }
        return 0.;
    }
    const string& param_value::as_string() const
    {
        if( f_value_type == k_string ) return *f_value.f_string;

        std::stringstream t_conv;
        if( f_value_type == k_bool ) t_conv << (as_bool() ? "true" : "false");
        else if( f_value_type == k_uint ) t_conv << as_uint();
        else if( f_value_type == k_int ) t_conv << as_int();
        else if( f_value_type == k_double ) t_conv << as_double();

        t_conv >> f_buffer;
        return f_buffer;
    }

    path param_value::as_path() const
    {
        if( f_value_type == k_string ) return path( *f_value.f_string );
        return path();
    }

    void param_value::clear()
    {
        if( f_value_type == k_bool ) f_value.f_bool = false;
        else if( f_value_type == k_uint ) f_value.f_uint = 0;
        else if( f_value_type == k_int ) f_value.f_int = 0;
        else if( f_value_type == k_double ) f_value.f_double = 0.;
        else if( f_value_type == k_string ) f_value.f_string->clear();
        return;
    }

    bool param_value::has_subset( const param& a_subset ) const
    {
        if( ! a_subset.is_value() ) return false;
        return true;
    }


    //************************************
    //***********  ARRAY  ****************
    //************************************

    param_array::param_array() :
            param(),
            f_contents()
    {
    }

    param_array::param_array( const param_array& orig ) :
            param( orig ),
            f_contents( orig.f_contents.size() )
    {
        for( unsigned ind = 0; ind < f_contents.size(); ++ind )
        {
            this->assign( ind, orig[ ind ].clone() );
        }
    }

    param_array::~param_array()
    {
        clear();
    }

    param_array& param_array::operator=( const param_array& rhs )
    {
        clear();
        for( unsigned ind = 0; ind < f_contents.size(); ++ind )
        {
            this->assign( ind, rhs[ ind ].clone() );
        }
        return *this;
    }

    bool param_array::has_subset( const param& a_subset ) const
    {
        if( ! a_subset.is_array() ) return false;
        const param_array& t_subset_array = a_subset.as_array();
        if( t_subset_array.size() > f_contents.size() ) return false;
        const_iterator t_this_it = f_contents.begin();
        const_iterator t_that_it = t_subset_array.begin();
        while( t_that_it != t_subset_array.end() ) // loop condition is on a_subset because it's smaller or equal to this
        {
            if( ! (*t_this_it)->has_subset( **t_that_it ) ) return false;
            ++t_this_it;
            ++t_that_it;
        }
        return true;
    }

    void param_array::resize( unsigned a_size )
    {
        unsigned curr_size = f_contents.size();
        for( unsigned ind = a_size; ind < curr_size; ++ind )
        {
            delete f_contents[ ind ];
        }
        f_contents.resize( a_size );
        return;
    }

    std::string param_array::to_string() const
    {
        stringstream out;
        string indentation;
        for ( unsigned i=0; i<param::s_indent_level; ++i )
            indentation += "    ";
        out << '\n' << indentation << "[\n";
        param::s_indent_level++;
        for( const_iterator it = begin(); it != end(); ++it )
        {
            out << indentation << "    " << **it << '\n';
        }
        param::s_indent_level--;
        out << indentation << "]\n";
        return out.str();
    }



    //************************************
    //***********  NODE  *****************
    //************************************

    param_node::param_node() :
            param(),
            f_contents()
    {
    }

    param_node::param_node( const param_node& orig ) :
            param( orig ),
            f_contents()
    {
        for( const_iterator it = orig.f_contents.begin(); it != orig.f_contents.end(); ++it )
        {
            add( it->first, it->second->clone() );
        }
    }

    param_node::~param_node()
    {
        clear();
    }

    param_node& param_node::operator=( const param_node& rhs )
    {
        clear();
        for( const_iterator it = rhs.f_contents.begin(); it != rhs.f_contents.end(); ++it )
        {
            this->replace( it->first, *it->second );
        }
        return *this;
    }

    bool param_node::has_subset( const param& a_subset ) const
    {
        if( ! a_subset.is_node() ) return false;
        const param_node& t_subset_node = a_subset.as_node();
        if( t_subset_node.size() > f_contents.size() ) return false;
        for( const_iterator t_subset_it = t_subset_node.begin(); t_subset_it != t_subset_node.end(); ++t_subset_it )
        {
            if( ! has( t_subset_it->first ) ) return false;
            if( ! f_contents.at( t_subset_it->first )->has_subset( *t_subset_it->second ) ) return false;
        }
        return true;
    }

    void param_node::merge( const param_node& a_object )
    {
        //DEBUG( dlog, "merging object with " << a_object.size() << " items:\n" << a_object );
        for( const_iterator it = a_object.f_contents.begin(); it != a_object.f_contents.end(); ++it )
        {
            if( ! has( it->first ) )
            {
                //DEBUG( dlog, "do not have object <" << it->first << "> = <" << *it->second << ">" );
                add( it->first, *it->second );
                continue;
            }
            param& t_param = (*this)[ it->first ];
            if( t_param.is_value() )
            {
                //DEBUG( dlog, "replacing the value of \"" << it->first << "\" <" << get_value( it->first ) << "> with <" << *it->second << ">" );
                replace( it->first, *it->second );
                continue;
            }
            if( t_param.is_node() && it->second->is_node() )
            {
                //DEBUG( dlog, "merging nodes")
                t_param.as_node().merge( it->second->as_node() );
                continue;
            }
            if( t_param.is_array() && it->second->is_array() )
            {
                //DEBUG( dlog, "appending array" );
                t_param.as_array().append( it->second->as_array() );
                continue;
            }
            //DEBUG( dlog, "generic replace" );
            this->replace( it->first, *it->second );
        }
    }

    std::string param_node::to_string() const
    {
        stringstream out;
        string indentation;
        for ( unsigned i=0; i<param::s_indent_level; ++i )
            indentation += "    ";
        out << '\n' << indentation << "{\n";
        param::s_indent_level++;
        for( const_iterator it = begin(); it != end(); ++it )
        {
            out << indentation << "    " << it->first << " : " << *(it->second) << '\n';
        }
        param::s_indent_level--;
        out << indentation << "}\n";
        return out.str();
    }




    SCARAB_API std::ostream& operator<<(std::ostream& out, const param& a_value)
    {
        return out << a_value.to_string();
    }


    SCARAB_API std::ostream& operator<<(std::ostream& out, const param_value& a_value)
    {
        return out << a_value.as_string();
    }


    SCARAB_API std::ostream& operator<<(std::ostream& out, const param_array& a_value)
    {
        return out << a_value.to_string();
    }


    SCARAB_API std::ostream& operator<<(std::ostream& out, const param_node& a_value)
    {
        return out << a_value.to_string();
    }

} /* namespace mantis */