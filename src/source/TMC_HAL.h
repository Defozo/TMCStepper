
#pragma once

#if defined(ARDUINO_ARCH_AVR)

    namespace TMCStepper_n {
        typedef uint8_t PinDef;

        class TMCPin {
        public:
            explicit TMCPin(const uint8_t _pin);
            void mode(const uint8_t mode) const;
            bool read() const;
            operator bool() const {
                return read();
            }

        protected:
            volatile uint8_t* const port = nullptr;
            uint8_t const bitMask;
        };

        class OutputPin : public TMCPin {
        public:
            OutputPin(const uint8_t _pin);
            void write(const bool state) const;
        };

        typedef TMCPin InputPin;
    }

#elif defined(ARDUINO_ARCH_SAM)

    namespace TMCStepper_n {

        typedef uint32_t PinDef;

        class TMCPin {
        public:
            explicit TMCPin(const uint32_t _pin);
            void mode(const uint8_t mode) const;
            bool read() const;
            operator bool() const { return read(); }
            operator uint32_t() const { return pin; }
        protected:
            uint32_t const pin;
        };

        class OutputPin : public TMCPin {
        public:
            OutputPin(const uint32_t _pin);
            void write(const bool state) const;
        };

        typedef TMCPin InputPin;
    }

#elif defined(TARGET_LPC1768)

    namespace TMCStepper_n {

        typedef uint16_t PinDef;

        class TMCPin {
        public:
            explicit TMCPin(const uint16_t _pin);
            void mode(const uint8_t mode) const;
            bool read() const;
            operator bool() const { return read(); }
            operator uint16_t() const { return pin; }
        protected:
            uint16_t const pin;
            static constexpr uint8_t pinDelay = 60;
        };

        class OutputPin : public TMCPin {
        public:
            OutputPin(const uint16_t _pin);
            void write(const bool state) const;
        };

        typedef TMCPin InputPin;
    }

    #define HardwareSerial HardwareSerial<>

    #ifndef __MARLIN_FIRMWARE__
        #include <SoftwareSPI.h>

        struct SPIClass { // Should be removed when LPC core gets full SPI class implementation
            SPIClass(const uint8_t spi_speed, const pin_t sck_pin, const pin_t miso_pin, const pin_t mosi_pin) :
                mosi(mosi_pin), miso(miso_pin), sck(sck_pin), speed(spi_speed) {
                    swSpiInit(spi_speed, sck_pin, mosi_pin);
                }

            void beginTransaction() const {
                swSpiBegin(sck, miso, mosi);
            }

            uint8_t transfer(uint8_t data) const {
                return swSpiTransfer(data, speed, sck, miso, mosi);
            }

            private:
                const pin_t mosi, miso, sck;
                const uint8_t speed;
        };
    #endif

#endif

#ifndef HIGH
    #define HIGH 1
#endif
#ifndef LOW
    #define LOW 0
#endif
#ifndef INPUT
    #define INPUT  0x00
#endif
#ifndef INPUT_PULLUP
    #define INPUT_PULLUP  0x01
#endif
#ifndef OUTPUT
    #define OUTPUT 0x01
#endif
#if !defined(MSBFIRST) && !(defined(ARDUINO_ARCH_SAM))
    #define MSBFIRST 1
#endif
#ifndef SPI_MODE3
    #define SPI_MODE3 0
#endif
