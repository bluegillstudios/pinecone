#include "../../include/arch/arm64/arm64.h"
#include "../../include/arch/arm64/context.h"
#include <string.h>

void* setup_initial_context(void (*entry)(void), void* stack_top) {
    context_t* ctx = (context_t*)((uint8_t*)stack_top - sizeof(context_t));
    memset(ctx, 0, sizeof(context_t));
    ctx->pc = (uint64_t)entry;
    ctx->sp = (uint64_t)stack_top;
    return ctx;
}
