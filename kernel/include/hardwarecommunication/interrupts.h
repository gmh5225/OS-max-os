//
// Created by 98max on 7/10/2022.
//

#ifndef MAX_OS_HARDWARECOMMUNICATION_INTERRUPTS_H
#define MAX_OS_HARDWARECOMMUNICATION_INTERRUPTS_H

#include <common/types.h>
#include <hardwarecommunication/port.h>
#include <system/gdt.h>
#include <system/multithreading.h>


namespace maxOS {
    namespace hardwarecommunication {

        class InterruptManager;

        class InterruptHandler {
        protected:
            maxOS::common::uint8_t interrupNumber;
            InterruptManager *interruptManager;

            InterruptHandler(maxOS::common::uint8_t interrupNumber, InterruptManager *interruptManager);

            ~InterruptHandler();

        public:
            virtual maxOS::common::uint32_t HandleInterrupt(maxOS::common::uint32_t esp);

        };

        class InterruptManager {
            friend class InterruptHandler;  //Declaring InterruptHandler as a friend class makes it possible for InterruptManager class to access all members (private and public) of InterrruptHandler class as if it were a member of that class.

        protected:

            static InterruptManager *ActiveInterruptManager;
            InterruptHandler *handlers[256];
            ThreadManager* threadManager;

            struct GateDescriptor {
                maxOS::common::uint16_t handlerAddressLowBits;
                maxOS::common::uint16_t gdt_codeSegmentSelector;
                maxOS::common::uint8_t reserved;
                maxOS::common::uint8_t access;
                maxOS::common::uint16_t handlerAddressHighBits;
            } __attribute__((packed));

            static GateDescriptor interruptDescriptorTable[256];

            struct InterruptDescriptorTablePointer {
                maxOS::common::uint16_t size;
                maxOS::common::uint32_t base;
            } __attribute__((packed));

            maxOS::common::uint16_t hardwareInterruptOffset;

            static void SetInterruptDescriptorTableEntry(maxOS::common::uint8_t interrupt,
                                                         maxOS::common::uint16_t codeSegmentSelectorOffset,
                                                         void (*handler)(),
                                                         maxOS::common::uint8_t DescriptorPrivilegeLevel,
                                                         maxOS::common::uint8_t DescriptorType);

            static void InterruptIgnore();

            //Various Interrupts
            static void HandleInterruptRequest0x00();

            static void HandleInterruptRequest0x01();

            static void HandleInterruptRequest0x02();

            static void HandleInterruptRequest0x03();

            static void HandleInterruptRequest0x04();

            static void HandleInterruptRequest0x05();

            static void HandleInterruptRequest0x06();

            static void HandleInterruptRequest0x07();

            static void HandleInterruptRequest0x08();

            static void HandleInterruptRequest0x09();

            static void HandleInterruptRequest0x0A();

            static void HandleInterruptRequest0x0B();

            static void HandleInterruptRequest0x0C();

            static void HandleInterruptRequest0x0D();

            static void HandleInterruptRequest0x0E();

            static void HandleInterruptRequest0x80();

            static void HandleInterruptRequest0x0F();

            static void HandleInterruptRequest0x31();

            static void HandleException0x00();

            static void HandleException0x01();

            static void HandleException0x02();

            static void HandleException0x03();

            static void HandleException0x04();

            static void HandleException0x05();

            static void HandleException0x06();

            static void HandleException0x07();

            static void HandleException0x08();

            static void HandleException0x09();

            static void HandleException0x0A();

            static void HandleException0x0B();

            static void HandleException0x0C();

            static void HandleException0x0D();

            static void HandleException0x0E();

            static void HandleException0x0F();

            static void HandleException0x10();

            static void HandleException0x11();

            static void HandleException0x12();

            static void HandleException0x13();

            static maxOS::common::uint32_t HandleInterrupt(maxOS::common::uint8_t interrupt, maxOS::common::uint32_t esp);

            maxOS::common::uint32_t DoHandleInterrupt(maxOS::common::uint8_t interrupt, maxOS::common::uint32_t esp);

            //PIC Cominunication
            Port8BitSlow programmableInterruptControllerMasterCommandPort;
            Port8BitSlow programmableInterruptControllerMasterDataPort;
            Port8BitSlow programmableInterruptControllerSlaveCommandPort;
            Port8BitSlow programmableInterruptControllerSlaveDataPort;


        public:
            InterruptManager(maxOS::common::uint16_t hardwareInterruptOffset, system::GlobalDescriptorTable *globalDescriptorTable, ThreadManager* threadManager);

            ~InterruptManager();

            maxOS::common::uint16_t HardwareInterruptOffset();

            void Activate();

            void Deactivate();

        };
    }
}

#endif //MAX_OS_HARDWARECOMMUNICATION_INTERRUPTS_H
