#include "cmdhandler.h"

char *setOutput(char *input)
{
    uint16_t RX_data_buffer_size = 10;
    char *RX_data_buffer = malloc_(RX_data_buffer_size);
    uint16_t index = 0;
    char DR = ' ';
    while (DR != '\0')
    {
        if (index >= RX_data_buffer_size)
        {
            RX_data_buffer_size += 10;
            RX_data_buffer = realloc_(RX_data_buffer, RX_data_buffer_size);
        }
        DR = *(input + index);
        *(RX_data_buffer + index) = DR;
        index++;
    }
    return RX_data_buffer;
}

char *getMainCommand(char *input)
{
    uint8_t buffer_size = 10;
    char *buffer = malloc_(buffer_size);
    uint8_t i = 0;
    char symbol = *input;
    while (symbol != ' ' && symbol != '\n')
    {
        symbol = *(input + i);
        if (buffer_size >= i)
        {
            buffer_size += 10;
            buffer = realloc_(buffer, buffer_size);
        }
        if (symbol == ' ')
        {
            *(buffer + i) = '\n';
            return buffer;
        }
        else
        {
            *(buffer + i) = symbol;
        }
        i++;
    }
    return buffer;
}

char *getSubCommand(char *input)
{
    char symbol = *input;
    uint8_t i = 0;
    while (symbol != ' ' && symbol != '\n')
    {
        i++;
        symbol = *(input + i);
    }
    if (symbol == ' ')
    {
        uint8_t buffer_size = 10;
        char *buffer = malloc_(buffer_size);
        uint8_t j = 0;
        i++;
        symbol = *(input + i);
        *(buffer + j) = symbol;
        while (/* symbol != ' ' && */ symbol != '\0')
        {
            symbol = *(input + i);
            if (buffer_size >= j)
            {
                buffer_size += 10;
                buffer = realloc_(buffer, buffer_size);
            }
            // if (symbol == ' ')
            // {
            //     *(buffer + j) = '\0';
            // }
            // else
            // {
            //     *(buffer + j) = symbol;
            // }
            *(buffer + j) = symbol;
            i++;
            j++;
        }
        return buffer;
    }
    return NULL;
}

uint8_t compareStr(const char *command_ptr, char *input_ptr)
{
    uint16_t index = 0;
    uint8_t command_symbol = *command_ptr;
    uint8_t input_symbol = *input_ptr;
    while (command_symbol != '\0' || input_symbol != '\n')
    {
        if (command_symbol != input_symbol)
            return 0;
        index++;
        command_symbol = *(command_ptr + index);
        input_symbol = *(input_ptr + index);
    }
    if ((command_symbol == '\0' && input_symbol != '\n') || (command_symbol != '\0' && input_symbol == '\n'))
        return 0;
    return 1;
}