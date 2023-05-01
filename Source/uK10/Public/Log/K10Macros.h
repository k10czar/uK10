#define RETURN_IF_NULL(ptr) \
if( ptr == nullptr ) return; \

#define RETURN_AND_LOG_IF_NULL(ptr, variableName) \
if( ptr == nullptr ) \
{ \
    UE_LOG( LogTemp, Error, TEXT("Returning Macro because of %s is a null pointer"), TEXT(variableName) ); \
    return; \
}