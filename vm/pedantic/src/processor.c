#include "processor.h"

ArResult processor_alloc(struct ArProcessor_T ** processor) {
    *processor = malloc(sizeof(struct ArProcessor_T));
    if(*processor == NULL) {
        return AR_ERROR_HOST_OUT_OF_MEMORY;
    }
    return AR_SUCCESS;
}

ArResult processor_initialize(struct ArProcessor_T * processor) {
    processor->vfreg = (float *) &processor->vreg;
    processor->vdreg = (double *) &processor->vreg;
    processor->vireg = (uint32_t *) &processor->vreg;
    return AR_SUCCESS;
}

ArResult processor_cycle(struct ArProcessor_T* processor) {
    // TODO: faire un cycle de CPU
    return AR_SUCCESS;
}

void processor_free(struct ArProcessor_T * processor) {

}