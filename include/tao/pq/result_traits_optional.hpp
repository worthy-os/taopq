// The Art of C++ / taopq
// Copyright (c) 2016-2018 Daniel Frey

#ifndef TAO_PQ_RESULT_TRAITS_OPTIONAL_HPP
#define TAO_PQ_RESULT_TRAITS_OPTIONAL_HPP

#include <optional>

#include <tao/pq/result_traits.hpp>
#include <tao/pq/row.hpp>

namespace tao
{
   namespace pq
   {
      template< typename T >
      struct result_traits< std::optional< T > >
      {
         static constexpr std::size_t size = result_traits_size< T >;

         [[nodiscard]] static std::optional< T > null()
         {
            return {};
         }

         [[nodiscard]] static std::optional< T > from( const char* value )
         {
            return result_traits< T >::from( value );
         }

         [[nodiscard]] static std::optional< T > from( const row& row )
         {
            for( std::size_t column = 0; column < row.columns(); ++column ) {
               if( !row.is_null( column ) ) {
                  return result_traits< T >::from( row );
               }
            }
            return null();
         }
      };

   }  // namespace pq

}  // namespace tao

#endif
