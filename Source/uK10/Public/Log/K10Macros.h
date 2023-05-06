#include "Logging/LogMacros.h"

#define RETURN_IF_NULL(ptr) \
if( ptr == nullptr ) return; \

#define RETURN_AND_LOG_IF_NULL(ptr, variableName) \
if( ptr == nullptr ) \
{ \
    UE_LOG( LogTemp, Error, TEXT("Returning Macro because of %s is a null pointer"), TEXT(variableName) ) \
    return; \
}

// #define DEFAULT_CONSOLE_LOG_CATEGORY LogTemp
// #define DEFAULT_CONSOLE_LOG_VERBOSITY Warning

#define CONSOLE_LOG( text, ... ) UE_LOG( LogTemp, Warning, TEXT(text), ##__VA_ARGS__ )

#define DISPLAY_LOG_CUSTOM( id, displaySeconds, color, text, ... ) if( GEngine ) GEngine->AddOnScreenDebugMessage( id, displaySeconds, color, FString::Printf( TEXT(text), ##__VA_ARGS__ ) );

#define DEFAULT_LOG_ID -1
#define DEFAULT_LOG_TIME 5.0f
#define DEFAULT_LOG_COLOR FColor::Yellow

#define DISPLAY_REPLACABLE_LOG( id, text, ... ) DISPLAY_LOG_CUSTOM( id, DEFAULT_LOG_TIME, DEFAULT_LOG_COLOR, text, ##__VA_ARGS__ )

#define DISPLAY_LOG( text, ... ) DISPLAY_LOG_CUSTOM_P1( DEFAULT_LOG_ID, DEFAULT_LOG_TIME, DEFAULT_LOG_COLOR, text, ##__VA_ARGS__ )

#define DISPLAY_AND_CONSOLE_LOG( text, ... ) DISPLAY_LOG_CUSTOM( DEFAULT_LOG_ID, DEFAULT_LOG_TIME, DEFAULT_LOG_COLOR, text, ##__VA_ARGS__ ) \
CONSOLE_LOG( text, ##__VA_ARGS__ );