//
// Created by 98max on 5/11/2022.
//

#ifndef MAXOS_NET_ETHERFRAME_H
#define MAXOS_NET_ETHERFRAME_H

#include <common/types.h>
#include <drivers/amd_am79c973.h>
#include <system/memorymanagement.h>

namespace maxOS{

    namespace net{

        //Structure the raw data
        struct EtherFrameHeader{

            common::uint64_t dstMAC_BE : 48;     //Destination MAC Address (Big Endian)
            common::uint64_t srcMAC_BE : 48;     //Source MAC Address (Big Endian)

            common::uint16_t etherType_BE;      //The type (Big Endian)

        }__attribute__ ((packed));

        typedef common::uint32_t EtherFrameFooter;

        class EtherFrameProvider;

        //EtherFrameHandler will be derived from ARP , IPv4 ,.....etc
        class EtherFrameHandler{

            protected:

                EtherFrameProvider* backend;
                common::uint16_t etherType_BE;

            public:
                EtherFrameHandler(EtherFrameProvider* backend, common::uint16_t etherType);
                ~EtherFrameHandler();

                virtual bool OnEtherFrameReceived(common::uint8_t* etherframePayload, common::uint32_t size);
                void Send(common::uint64_t dstMAC_BE, common::uint8_t* data, common::uint32_t size);


        };

        //The backend for the handler
        class EtherFrameProvider : public drivers::RawDataHandler{
            friend class EtherFrameHandler;
            protected:

                EtherFrameHandler* handlers[65535];

            public:
                EtherFrameProvider(drivers::amd_am79c973* backend);
                ~EtherFrameProvider();

                bool OnRawDataReceived(common::uint8_t* buffer, common::uint32_t size);
                void Send(common::uint64_t dstMAC_BE, common::uint16_t etherType_BE, common::uint8_t* buffer, common::uint32_t size);

                common::uint32_t GetIPAddress();
                common::uint64_t GetMACAddress();

        };

    }

}

#endif //MAXOS_NET_ETHERFRAME_H
