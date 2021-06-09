
GCCPARAMS = -m32 -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore -Wno-write-strings
ASPARAMS = --32
LDPARAMS = -melf_i386


objects = obj/loader.o \
          obj/gdt.o \
          obj/Drivers/driver.o \
          obj/HComms/port.o \
          obj/HComms/interruptstubs.o \
          obj/HComms/interrupts.o \
          obj/HComms/pci.o \
          obj/Drivers/keyboard.o \
          obj/Drivers/mouse.o \
          obj/kernel.o
all: main

%.o: %.cpp
	g++ $(GCCPARAMS) -c -o $@ $<

%.o: %.s
	as $(ASPARAMS) -o $@ $<

obj/%.o: %.cpp
	mkdir -p $(@D)
	g++ $(GCCPARAMS) -c -o $@ $<

obj/%.o: %.s
	mkdir -p $(@D)
	as $(ASPARAMS) -o $@ $<

Kernel.bin: linker.ld $(objects)
	ld $(LDPARAMS) -T $< -o $@ $(objects)

Kernel.iso: Kernel.bin
	mkdir iso
	mkdir iso/boot
	mkdir iso/boot/grub
	cp Kernel.bin iso/boot/Kernel.bin
	echo 'set timeout=0'                      > iso/boot/grub/grub.cfg
	echo 'set default=0'                     >> iso/boot/grub/grub.cfg
	echo ''                                  >> iso/boot/grub/grub.cfg
	echo 'menuentry "Drishti OS" {' >> iso/boot/grub/grub.cfg
	echo '  multiboot /boot/Kernel.bin'    >> iso/boot/grub/grub.cfg
	echo '  boot'                            >> iso/boot/grub/grub.cfg
	echo '}'                                 >> iso/boot/grub/grub.cfg
	grub-mkrescue --output=builds/Kernel.iso iso
	rm -rf iso

clean:
	rm -rf $< $(objects)
	rm -rf iso
	clear

main: Kernel.bin $(objects) Kernel.iso
	rm -rf $< $(objects)
	rm -rf iso
	clear

RemoveBuilds: builds/
	rm -rf $<
	mkdir builds
