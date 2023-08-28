#pragma once


enum SerialFrameResultStatus
{
    SERIAL_RESULT_NONE,
    SERIAL_RESULT_OK,
    SERIAL_RESULT_RESPONSE_ERROR,
    SERIAL_RESULT_FAIL_TO_SETTING,
    SERIAL_RESULT_FAIL_TO_CONNECT,
    SERIAL_RESULT_FAIL_TO_SEND_DATA,
    SERIAL_RESULT_FAIL_TO_RECEIVE_DATA,
};

enum ConnectionCommandType
{
    SET_BOOL,       GET_BOOL,

    SET_INT_16,     GET_INT_16,
    SET_INT_32,     GET_INT_32,

    SET_UINT_16,    GET_UINT_16,
    SET_UINT_32,    GET_UNINT_32,

    SET_FLOAT_32,   GET_FLOAT_32,
};

struct SerialFrameResult
{
    SerialFrameResultStatus status;
    uint8_t errorCode;
};