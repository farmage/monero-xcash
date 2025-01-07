// Copyright (c) 2017-2022, The Monero Project
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without modification, are
// permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice, this list of
//    conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice, this list
//    of conditions and the following disclaimer in the documentation and/or other
//    materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its contributors may be
//    used to endorse or promote products derived from this software without specific
//    prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL
// THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
// STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF
// THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//

// device_io_dummy
// Main goal of device_io_dummy is to emulate a hw::io::device_io without the need to actually
// connect a device.
// Many operating systems do not support giving raw USB access to a process (android), or don't
// support that at all (hi iOS), therefore other means of connection can be used, either USB
// abstraction provided by the OS (monerujo), or BLE (also monerujo).
// Monerujo implementation is written in Java, which makes it a nice fit for iOS, but makes the
// code extremely unportable, so for this reason the code in here is written in CPP.
// Data transport is made available in wallet2_api.h, so wallet developers can easily plug their
// own USB/BLE/other transport layer.

#ifdef HIDAPI_DUMMY
#include <boost/scope_exit.hpp>
#include "log.hpp"
#include "device_io_dummy.hpp"
#include "device_ledger.hpp"


bool hw::io::device_io_dummy::stateIsConnected = false;
unsigned char* hw::io::device_io_dummy::sendToDevice = {};
size_t hw::io::device_io_dummy::sendToDeviceLength = 0;
unsigned char* hw::io::device_io_dummy::receivedFromDevice = {};
size_t hw::io::device_io_dummy::receivedFromDeviceLength = 0;
bool hw::io::device_io_dummy::waitsForDeviceSend = false;
bool hw::io::device_io_dummy::waitsForDeviceReceive = false;

namespace hw {
    namespace io {

#undef MONERO_DEFAULT_LOG_CATEGORY
#define MONERO_DEFAULT_LOG_CATEGORY "device.io_dummy"
        device_io_dummy::device_io_dummy(int a, int b, int c, int d) {
            MDEBUG("device_io_dummy(a: " << a << ", b: " << b << ", c: " << c << ", d: " << d <<")");
        }

        void device_io_dummy::init() {
            MDEBUG("init()");
        }

        void device_io_dummy::connect(void *params) {
            MDEBUG("connect(" << params << ")");
            stateIsConnected = true;
        }

        void device_io_dummy::connect(const std::vector<hw::io::hid_conn_params>& known_devices) {
            MDEBUG("connect([");
            for (const auto &item: known_devices) {
                MDEBUG("{   interface_number: " << item.interface_number);
                MDEBUG("    pid             : " << item.pid);
                MDEBUG("    usage_page      : " << item.usage_page);
                MDEBUG("    vid             : " << item.vid << " },");
            }
            MDEBUG("])");
            stateIsConnected = true;
        }

        bool device_io_dummy::connected() const {
            MDEBUG("connected()");
            return stateIsConnected;
        }

        int device_io_dummy::exchange(unsigned char *command, unsigned int cmd_len, unsigned char *response, unsigned int max_resp_len, bool user_input)  {
            MDEBUG("exchange(): locking mutex");
            boost::unique_lock<boost::mutex> lock(mutex);
            sendToDevice = command;
            sendToDeviceLength = cmd_len;
            waitsForDeviceSend = true;
            waitsForDeviceReceive = true;
            MDEBUG("exchange(): waitsForDeviceSend");
            // NOTE: waitsForDeviceSend should be changed by external code
            while (waitsForDeviceSend) {
                usleep(1000);
                MDEBUG("exchange(): waitsForDeviceSend (still)");
            }

            MDEBUG("exchange(): waitsForDeviceReceive");
            while (waitsForDeviceReceive) {
                usleep(1000);
                MDEBUG("exchange(): waitsForDeviceReceive (still)");
            }

            if (receivedFromDeviceLength > max_resp_len) {
                MDEBUG("exchange(): receivedFromDeviceLength ("<<receivedFromDeviceLength<<") is larger than max_resp_len ("<<max_resp_len<<")");
                return 1;
            }

            memset(response,0,max_resp_len);
            memcpy(response, receivedFromDevice, receivedFromDeviceLength);
            return receivedFromDeviceLength;
        }

        void device_io_dummy::disconnect()  {
            MDEBUG("disconnect()");
        }

        void device_io_dummy::release()  {
            MDEBUG("release()");
        }



    }
}
#endif // HAVE_HIDAPI