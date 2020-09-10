"""
Script for automatic interrupts generation
"""

# from string import Template as tmpl
from os import path

class Generator(object):
    """
    Generator is a class which generates low-level interrupts and high level handlers for KIMS
    """
    def __init__(self, wdir='.', irq_offset=0x20, table_size=256):
        """
        Constructor

        :param wdir Working directory (root directory of kims files)
        :param irq_offset Number of first IRQ in table
        :param table_size Number of interrupt to generate
        """

        self.llfile = path.join(wdir, 'llkims.S')
        self.hbfile = path.join(wdir, 'hbkims.h')
        self.settings = {
                'irq_offset': irq_offset,
                'tbl_size': table_size,
        }
    def __pad_code(code: str, pad_count: int = 1, pad_sym: str = '\t') -> str:
        new_code = code.split('\n')
        new_code = '\n'.join([''.join([pad_sym for i in range(pad_count)]) + item for item in new_code])
        return new_code
    def generate_handlers_bindings(self, interrupt_template):
        """
            :param interrupt_template Template of interrupts registering

            Interrupt template has variables:
                {num} - number of the interrupt in the table
                {base_intrname} - base name of an low-level interrupt handler (for example - intr_<num>)
        """
        with open(self.hbfile, 'tw') as f:
            f.write("// This file is auto-generated, do not edit it, all changes - into genkims.py\n")
            for i in range(self.settings['tbl_size']):
                f.write(interrupt_template.format(num=i, base_intrname='intr_') + '\n')
            
    def generate_lowlevel(self, interrupt_template, isrhandler_template, irqhandler_template):
        """
        Lowlevel interrupts generator

        :param interrupt_template Template of interrupts.
        :param isrhandler_template Template of an isr handler
        :param irqhandler_template Template of an irq handler

        Interrupt template has variables:
            {beg} - beginning of the interrupt (for example: ISR - cli & push ..., IRQ - push ...)
            {num} - number of the interrupt in the table
            {handler} - IRQ/ISR low level handler
        """
        with open(self.llfile, 'tw') as f:
            irqhandler_template = Generator.__pad_code(irqhandler_template)
            isrhandler_template = Generator.__pad_code(isrhandler_template)

            f.write(f"""# This code is auto-generated, please do not edit it, make all changes into genkims.py
.section .text

irq_common_handler:
{irqhandler_template}
isr_common_handler:
{isrhandler_template}
""")
            for num in range(self.settings['tbl_size']):
                if num >= self.settings['irq_offset'] and num <= self.settings['irq_offset'] + 15:
                    llirqhandler_code = Generator.__pad_code(interrupt_template.format(beg="""
push $0""", handler="irq_common_handler", num=num))
                    f.write(f"""
.global intr_{num}
intr_{num}:
{llirqhandler_code}
""")
                elif num in [8] + list(range(10, 14 + 1)):
                    llisrehandler_code = Generator.__pad_code(interrupt_template.format(beg="""cli
""", handler="isr_common_handler", num=num))
                    f.write(f"""
.global intr_{num}
intr_{num}:
{llisrehandler_code}
""")
                else:
                    llisrhandler_code = Generator.__pad_code(interrupt_template.format(beg="""cli
pushl $0""", handler="isr_common_handler", num=num))
                    f.write(f"""
.global intr_{num}
intr_{num}:
{llisrhandler_code}
""")
                pass


gen = Generator()
gen.generate_lowlevel(isrhandler_template="""pusha
push %ds
push %es
push %gs
push %fs
mov $0x10, %ax
mov %ax, %ds
mov %ax, %es
mov %ax, %gs
mov %ax, %fs
.extern kims_interrupt_handler
call kims_interrupt_handler
pop %fs
pop %gs
pop %es
pop %ds
popa
add $8, %esp
sti
iret
""", irqhandler_template="""pusha
push %ds
push %es
push %gs
push %fs
mov $0x10, %ax
mov %ax, %ds
mov %ax, %es
mov %ax, %gs
mov %ax, %fs
.extern kims_hwinterrupt_handler
call kims_hwinterrupt_handler
pop %fs
pop %es
pop %gs
pop %ds
popa
add $8, %esp
iret
""", interrupt_template="""{beg}
pushl ${num}
jmp {handler}
""")

gen.generate_handlers_bindings(interrupt_template="""extern void {base_intrname}{num}(void);kims_set_native_entry({num},kims_convert_dinfo_to_desc((kims_interrupt_descriptor_info_t){{.kind=KIMS_IDK_INTR32,.v={{.intr32={{.base=(uint32_t){base_intrname}{num},.ksel=0x08,.storage_seg=false,.present=true,.dpl=0x0}}}}}}));""")

"""
extern void interrupt_##n(void); kims_set_native_entry(n, kims_convert_dinfo_to_desc((kims_interrupt_descriptor_info_t){ \
      .kind = KIMS_IDK_INTR32,                                            \
      .v = {                                                              \
        .intr32 = {                                                       \
          .base = (uint32_t)interrupt_##n,                                \
          .ksel = 0x08,                                                   \
          .storage_seg = false,                                           \
          .present = true,                                                \
          .dpl = 0x0,                                                     \
        }                                                                 \
      }                                                                   \
    }))
"""
