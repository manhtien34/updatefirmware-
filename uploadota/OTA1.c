#include <stdio.h>
#include <string.h>
#include <stdint.h>

char file_hex[1024 * 50] = R"(
:100000007006002089010008B90A0008B50A000836
:100000007006002089010008B90A0008B50A000836
:100000007006002089010008B90A0008B50A000836
:100000007006002089010008B90A0008B50A000836
:100000007006002089010008B90A0008B50A000836
:100000007006002089010008B90A0008B50A000836
)";

int8_t char_to_byte(char c) {
    if (c >= '0' && c <= '9') {
        return c - '0';
    } else if (c >= 'A' && c <= 'F') {
        return c - 'A' + 10;
    } else if (c >= 'a' && c <= 'f') {
        return c - 'a' + 10;
    }
    return -1;
}

void convert_string_to_array_hex(char *input, uint8_t *output) {
    uint8_t index = 0;
    if (*input == ':') {
        input++;
        while (*input != '\0' && *(input + 1) != '\0') {
            uint8_t hex_value = (char_to_byte(*input) << 4) | char_to_byte(*(input + 1));
            input += 2;
            output[index++] = hex_value;
           // printf("%02x ", hex_value);
        }
       // printf("\n");
    }
}

enum {
    STATUS_OK,
    STATUS_ERROR
};

uint8_t check_some(uint8_t *buff, uint8_t len) {
    uint8_t sum = 0;
    for (uint8_t i = 0; i < len - 1; i++) {
        sum += buff[i];
    }
    sum = ~sum;
    sum += 1;
    if (sum == buff[len - 1]) {
        return STATUS_OK;
    }
    return STATUS_ERROR;
}

void swap(uint8_t *a, uint8_t *b) {
    uint8_t temp = *a;
    *a = *b;
    *b = temp;
}

void swap_4_byte(uint8_t *data, uint8_t len) {
    for (int i = 0; i < len; i += 4) {
        swap(&data[i + 0], &data[i + 3]);
        swap(&data[i + 1], &data[i + 2]);
    }
}

void printf_data(uint8_t *data, uint8_t len) {
    for (uint8_t i = 0; i < len; i++) {  // Thay từ -0 thành 0
        printf("%02X ", data[i]);  // Sửa từ data[1] thành data[i]
    }
    printf("\n");
}

int main() {
    char *token = strtok(file_hex, "\n");
    while (token != NULL) {
        uint8_t hex_data[21];
        convert_string_to_array_hex(token, hex_data);
        if (check_some(hex_data, hex_data[0] + 5) != STATUS_OK) {
            break;
        } 
        if (hex_data[3] == 0x00) {
            swap_4_byte(&hex_data[4], hex_data[0]);
            min_send_farem(&hex_data[4], hex_data[0]);
        }
        printf_data(hex_data, hex_data[0] + 5); 
        token = strtok(NULL, "\n");
    }
    return 0;
}
