
#ifndef MLX_LOSSY_H
#define MLX_LOSSY_H

#define MLX_LOSSY_VL_CFG 0xff80

typedef struct {
        uint16_t ignore_buffer_mask;
        uint16_t ignore_credit_mask;
} lossy_config_t;

#endif
