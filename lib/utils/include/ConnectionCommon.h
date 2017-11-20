/**
 * This file is part of the LePi Project:
 * https://github.com/cosmac/LePi
 *
 * MIT License
 *
 * Copyright (c) 2017 Andrei Claudiu Cosma
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#pragma once

constexpr size_t kMaxWidth{160};
constexpr size_t kMaxHeight{120};
constexpr size_t kMaxBytesPerPixel{2};

// Request message type
enum RequestType { FRAME_REQUEST,   // Request a frame
                   I2C_REQUEST,     // Request an I2C command
                   UNKNOWN_REQUEST  // Unknown request
                 };

// Request message status
enum RequestStatus { FRAME_READY,   // The response contains a valid frame
                     NO_FRAME,      // No frame ready to be read [We can avoid this by repeating last frame]
                     I2C_SUCCEED,   // I2C command was applied with success
                     I2C_FAILED,    // I2C command failed
                     RESEND         // If the client message was something unknown, ask for a resend
                   };

// Subscriber uses this message to ask publisher for data
struct RequestMessage {
    RequestType req_type{UNKNOWN_REQUEST};
    int req_cmd{-1};
};

// Publisher uses this message in response to the subscriber request
struct ResponseMessage {
    RequestType req_type{UNKNOWN_REQUEST};
    RequestStatus req_status{RESEND};
    uint32_t width{0};
    uint32_t height{0};
    uint32_t bpp{0};
    uint64_t frame_id{0};
    char frame[kMaxWidth * kMaxHeight * kMaxBytesPerPixel];
    double sensor_temperature{0.0};
};
