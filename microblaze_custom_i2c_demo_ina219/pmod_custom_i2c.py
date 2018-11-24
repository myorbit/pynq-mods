import math
from . import Pmod
from . import PMOD_GROVE_G4


__author__ = "Martin Hofmann"
__copyright__ = "Copyright 2018"
__email__ = ""


PMOD_CUSTOM_PROGRAM = "pmod_custom_i2c.bin"
CONFIG_IOP_SWITCH = 0x1
GET_VALUE = 0xD
RESET = 0xF


class Custom_I2C(object):

    def __init__(self, mb_info, gr_pin):
        if gr_pin not in [PMOD_GROVE_G4]:
            raise ValueError("Group number can only be G4.")

        self.microblaze = Pmod(mb_info, PMOD_CUSTOM_PROGRAM)
        self.microblaze.write_mailbox(0, gr_pin)
        self.microblaze.write_blocking_command(CONFIG_IOP_SWITCH)
        self.reset()

    def reset(self):
        self.microblaze.write_blocking_command(RESET)

    def get_value(self):
        self.microblaze.write_blocking_command(GET_VALUE)
        data = self.microblaze.read_mailbox(0)
        return data
