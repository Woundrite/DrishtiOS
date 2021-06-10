#include "../includes/Drivers/vga.h"

namespace Drishti{
    namespace Drivers{

        VideoGraphicsArray::VideoGraphicsArray():Misc(0x3c2),CRTCIndexPort(0x3d4), CRTCDataPort(0x3d5), SequencerIndexPort(0x3c4), SequencerDataPort(0x3c5), GraphicsControllerIndexPort(0x3ce), GraphicsControllerDataPort(0x3cf), AttributeControllerIndexPort(0x3c0), AttributeControllerReadPort(0x3c1), AttributeControllerWritePort(0x3c0), AttributeControllerResetPort(0x3da){
            //...
        }

        VideoGraphicsArray::~VideoGraphicsArray(){
            //...
        }

        void VideoGraphicsArray::WriteRegisters(Types::uint8_t* Registers){
            Misc.Write(*(Registers++));

            for(Types::uint8_t i =0; i < 5; i++){
                SequencerIndexPort.Write(i);
                SequencerDataPort.Write(*(Registers++));
            }

            CRTCIndexPort.Write(0x03);
            CRTCDataPort.Write(CRTCDataPort.Read() | 0x80);
            CRTCIndexPort.Write(0x11);
            CRTCDataPort.Write(CRTCDataPort.Read()  & ~0x80);

            Registers[0x03] = Registers[0x03] | 0x80;
            Registers[0x11] = Registers[0x03] & ~0x80;

            for(Types::uint8_t i = 0; i < 25; i++){
                CRTCIndexPort.Write(i);
                CRTCDataPort.Write(*(Registers++));
            }

            for(Types::uint8_t i =0; i < 9; i++){
                GraphicsControllerIndexPort .Write(i);
                GraphicsControllerDataPort.Write(*(Registers++));
            }

            for(Types::uint8_t i = 0; i < 21; i++){
                AttributeControllerResetPort.Read();
                AttributeControllerIndexPort.Write(i);
                AttributeControllerWritePort.Write(*(Registers++));
            }

            AttributeControllerResetPort.Read();
            AttributeControllerWritePort.Write(0x20);
        }

        bool VideoGraphicsArray::SupportsMode(Types::uint32_t Width, Types::uint32_t Height, Types::uint32_t ColorDepth){
            return Width == 320 && Height == 200 && ColorDepth == 8;
        }

        bool VideoGraphicsArray::SetMode(Types::uint32_t Width, Types::uint32_t Height, Types::uint32_t ColorDepth){
            if(!SupportsMode(Width, Height, ColorDepth))
                return false;
            
            unsigned char g_320x200x256[] = {
                /* MISC */
                    0x63,
                /* SEQ */
                    0x03, 0x01, 0x0F, 0x00, 0x0E,
                /* CRTC */
                    0x5F, 0x4F, 0x50, 0x82, 0x54, 0x80, 0xBF, 0x1F,
                    0x00, 0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                    0x9C, 0x0E, 0x8F, 0x28,	0x40, 0x96, 0xB9, 0xA3,
                    0xFF,
                /* GC */
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x05, 0x0F,
                    0xFF,
                /* AC */
                    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                    0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
                    0x41, 0x00, 0x0F, 0x00,	0x00
            };
            WriteRegisters(g_320x200x256);
            return true;
        }

        Types::uint8_t* VideoGraphicsArray::GetFrameBufferSegment(){
            GraphicsControllerIndexPort.Write(0x06);
            Types::uint8_t SegmentNumber = ((GraphicsControllerDataPort.Read() >> 2) & 0x03);
            switch(SegmentNumber){
                case 0: return (Types::uint8_t*)0x00000;
                case 1: return (Types::uint8_t*)0xA0000;
                case 2: return (Types::uint8_t*)0xB0000;
                case 3: return (Types::uint8_t*)0xB8000;
            }
        }

        void VideoGraphicsArray::PutPixel(Types::uint32_t X, Types::uint32_t Y, Types::uint8_t ColorIndex){
            Types::uint8_t* PixelAddress = GetFrameBufferSegment() + 320*Y + X;
            *PixelAddress = ColorIndex;
        }

        Types::uint8_t VideoGraphicsArray::GetColorIndex(Types::uint8_t R, Types::uint8_t G, Types::uint8_t B){
            if(R == 0x00 && G == 0x00 && B == 0xA8)
                return 0x01;
        }

        void VideoGraphicsArray::PutPixel(Types::uint32_t X, Types::uint32_t Y, Types::uint8_t R, Types::uint8_t G, Types::uint8_t B){
            PutPixel(X, Y, GetColorIndex(R, G, B));
        }
    }
}