#ifndef UTIL_H
#define UTIL_H

#include <functional>
#include <iostream> // needed for ShallowCopy...                                                                                                                                   
#include <memory>

#include <boost/throw_exception.hpp>

#include <EventLoop/Worker.h>

#ifdef EL_RETURN_CHECK
#undef EL_RETURN_CHECK
#endif
#define EL_RETURN_CHECK( CONTEXT, EXP )                     \
  do {                                                      \
  if( ! EXP.isSuccess() ) {                                 \
  Error( CONTEXT,                                           \
    XAOD_MESSAGE( "Failed to execute: %s" ),                \
         #EXP );                                            \
  return EL::StatusCode::FAILURE;                           \
  }                                                         \
  } while( false )
#endif //UTIL_H
