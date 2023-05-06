#define RETURN_IF_NULL(ptr) \
if( ptr == nullptr ) return; \

#define RETURN_AND_LOG_IF_NULL(ptr, variableName) \
if( ptr == nullptr ) \
{ \
    UE_LOG( LogTemp, Error, TEXT("Returning Macro because of %s is a null pointer"), TEXT(variableName) ); \
    return; \
}

#define DISPLAY_LOG_CUSTOM( id, displaySeconds, color, text ) \
if( GEngine ) GEngine->AddOnScreenDebugMessage( id, displaySeconds, color, TEXT( text ) );

#define DISPLAY_LOG_CUSTOM_P1( id, displaySeconds, color, text, parameter1 ) \
if( GEngine ) GEngine->AddOnScreenDebugMessage( id, displaySeconds, color, FString::Printf( TEXT(text), parameter1 ) );
    
#define DISPLAY_LOG_CUSTOM_P2( id, displaySeconds, color, text, parameter1, parameter2 ) \
if( GEngine ) GEngine->AddOnScreenDebugMessage( id, displaySeconds, color, FString::Printf( TEXT(text), parameter1, parameter2 ) );
    
#define DISPLAY_LOG_CUSTOM_P3( id, displaySeconds, color, text, parameter1, parameter2, parameter3 ) \
if( GEngine ) GEngine->AddOnScreenDebugMessage( id, displaySeconds, color, FString::Printf( TEXT(text), parameter1, parameter2, parameter3 ) );
    
#define DISPLAY_LOG_CUSTOM_P4( id, displaySeconds, color, text, parameter1, parameter2, parameter3, parameter4 ) \
if( GEngine ) GEngine->AddOnScreenDebugMessage( id, displaySeconds, color, FString::Printf( TEXT(text), parameter1, parameter2, parameter3, parameter4 ) );
    
#define DISPLAY_LOG_CUSTOM_P5( id, displaySeconds, color, text, parameter1, parameter2, parameter3, parameter4, parameter5 ) \
if( GEngine ) GEngine->AddOnScreenDebugMessage( id, displaySeconds, color, FString::Printf( TEXT(text), parameter1, parameter2, parameter3, parameter4, parameter5 ) );

#define DEFAULT_LOG_ID -1
#define DEFAULT_LOG_TIME 5.0f
#define DEFAULT_LOG_COLOR FColor::Yellow

#define DISPLAY_REPLACABLE_LOG( id, text ) DISPLAY_LOG_CUSTOM( id, DEFAULT_LOG_TIME, DEFAULT_LOG_COLOR, text )
#define DISPLAY_REPLACABLE_LOG_P1( id, text, parameter1 ) DISPLAY_LOG_CUSTOM_P1( id, DEFAULT_LOG_TIME, DEFAULT_LOG_COLOR, text, parameter1 )
#define DISPLAY_REPLACABLE_LOG_P2( id, text, parameter1, parameter2 ) DISPLAY_LOG_CUSTOM_P2( id, DEFAULT_LOG_TIME, DEFAULT_LOG_COLOR, text, parameter1, parameter2 )
#define DISPLAY_REPLACABLE_LOG_P3( id, text, parameter1, parameter2, parameter3 ) DISPLAY_LOG_CUSTOM_P3( id, DEFAULT_LOG_TIME, DEFAULT_LOG_COLOR, text, parameter1, parameter2, parameter3 )
#define DISPLAY_REPLACABLE_LOG_P4( id, text, parameter1, parameter2, parameter3, parameter4 ) DISPLAY_LOG_CUSTOM_P4( id, DEFAULT_LOG_TIME, DEFAULT_LOG_COLOR, text, parameter1, parameter2, parameter3, parameter4 )
#define DISPLAY_REPLACABLE_LOG_P5( id, text, parameter1, parameter2, parameter3, parameter4, parameter5 ) DISPLAY_LOG_CUSTOM_P5( id, DEFAULT_LOG_TIME, DEFAULT_LOG_COLOR, text, parameter1, parameter2, parameter3, parameter4, parameter5 )

#define DISPLAY_LOG( text ) DISPLAY_LOG_CUSTOM( DEFAULT_LOG_ID, DEFAULT_LOG_TIME, DEFAULT_LOG_COLOR, text )
#define DISPLAY_LOG_P1( text, parameter1 ) DISPLAY_LOG_CUSTOM_P1( DEFAULT_LOG_ID, DEFAULT_LOG_TIME, DEFAULT_LOG_COLOR, text, parameter1 )
#define DISPLAY_LOG_P2( text, parameter1, parameter2 ) DISPLAY_LOG_CUSTOM_P2( DEFAULT_LOG_ID, DEFAULT_LOG_TIME, DEFAULT_LOG_COLOR, text, parameter1, parameter2 )
#define DISPLAY_LOG_P3( text, parameter1, parameter2, parameter3 ) DISPLAY_LOG_CUSTOM_P3( DEFAULT_LOG_ID, DEFAULT_LOG_TIME, DEFAULT_LOG_COLOR, text, parameter1, parameter2, parameter3 )
#define DISPLAY_LOG_P4( text, parameter1, parameter2, parameter3, parameter4 ) DISPLAY_LOG_CUSTOM_P4( DEFAULT_LOG_ID, DEFAULT_LOG_TIME, DEFAULT_LOG_COLOR, text, parameter1, parameter2, parameter3, parameter4 )
#define DISPLAY_LOG_P5( text, parameter1, parameter2, parameter3, parameter4, parameter5 ) DISPLAY_LOG_CUSTOM_P5( DEFAULT_LOG_ID, DEFAULT_LOG_TIME, DEFAULT_LOG_COLOR, text, parameter1, parameter2, parameter3, parameter4, parameter5 )

#define DISPLAY_AND_CONSOLE_LOG( text ) \
    DISPLAY_LOG_CUSTOM( DEFAULT_LOG_ID, DEFAULT_LOG_TIME, DEFAULT_LOG_COLOR, text )\
    UE_LOG( LogTemp, Warning, TEXT(text) );
#define DISPLAY_AND_CONSOLE_LOG_P1( text, parameter1 ) \
    DISPLAY_LOG_CUSTOM_P1( DEFAULT_LOG_ID, DEFAULT_LOG_TIME, DEFAULT_LOG_COLOR, text, parameter1 )\
    UE_LOG( LogTemp, Warning, TEXT(text), TEXT(parameter1) );
// #define DISPLAY_AND_CONSOLE_LOG_P2( text, parameter1, parameter2 ) \
//     DISPLAY_LOG_CUSTOM_P2( DEFAULT_LOG_ID, DEFAULT_LOG_TIME, DEFAULT_LOG_COLOR, text, parameter1, parameter2 )\
//     UE_LOG( LogTemp, Warning, TEXT(text), TEXT(parameter1, TEXT(parameter2) );
// #define DISPLAY_AND_CONSOLE_LOG_P3( text, parameter1, parameter2, parameter3 ) \
//     DISPLAY_LOG_CUSTOM_P3( DEFAULT_LOG_ID, DEFAULT_LOG_TIME, DEFAULT_LOG_COLOR, text, parameter1, parameter2, parameter3 )\
//     UE_LOG( LogTemp, Warning, TEXT(text), TEXT(parameter1), TEXT(parameter2), TEXT(parameter3) );
// #define DISPLAY_AND_CONSOLE_LOG_P4( text, parameter1, parameter2, parameter3, parameter4 ) \
//     DISPLAY_LOG_CUSTOM_P4( DEFAULT_LOG_ID, DEFAULT_LOG_TIME, DEFAULT_LOG_COLOR, text, parameter1, parameter2, parameter3, parameter4 )\
//     UE_LOG( LogTemp, Warning, TEXT(text), TEXT(parameter1), TEXT(parameter2), TEXT(parameter3), TEXT(parameter4) );
// #define DISPLAY_AND_CONSOLE_LOG_P5( text, parameter1, parameter2, parameter3, parameter4, parameter5 ) \
//     DISPLAY_LOG_CUSTOM_P5( DEFAULT_LOG_ID, DEFAULT_LOG_TIME, DEFAULT_LOG_COLOR, text, parameter1, parameter2, parameter3, parameter4, parameter5 )\
//     UE_LOG( LogTemp, Warning, TEXT(text), TEXT(parameter1), TEXT(parameter2), TEXT(parameter3), TEXT(parameter4), TEXT(parameter5) );