#if !defined (APPL_NM_H)
# define APPL_NM_H

#include "Nm.h"

FUNC( void, NM_CODE ) WLC_CANNM_StateChangeNotification( CONST( NetworkHandleType, AUTOMATIC ) nmNetworkHandle,
                                                         CONST( Nm_StateType, AUTOMATIC) nmPreviousState,
                                                         CONST( Nm_StateType, AUTOMATIC ) nmCurrentState );

#endif
