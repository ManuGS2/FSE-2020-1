import os
import sys
import time
from datetime import datetime
import smbus

def _bcd_to_int(bcd):
    """Decode a 2x4bit BCD to a integer.
    """
    out = 0
    for d in (bcd >> 4, bcd):
        for p in (1, 2, 4 ,8):
            if d & 1:
                out += p
            d >>= 1
        out *= 10
    return out / 10


class DS1307():
    _REG_SECONDS = 0x00
    _REG_MINUTES = 0x01
    _REG_HOURS = 0x02
    _REG_DAY = 0x03
    _REG_DATE = 0x04
    _REG_MONTH = 0x05
    _REG_YEAR = 0x06
    _REG_CONTROL = 0x07


    def __init__(self, twi=1, addr=0x68):
        self._bus = smbus.SMBus(twi)
        self._addr = addr


    def _read(self, data):
        return self._bus.read_byte_data(self._addr, data)


    def _read_seconds(self):
        return _bcd_to_int(self._read(self._REG_SECONDS))


    def _read_minutes(self):
        return _bcd_to_int(self._read(self._REG_MINUTES))


    def _read_hours(self):
        d = self._read(self._REG_HOURS)
        if (d & 0x40) != 0x40:
            return _bcd_to_int(d & 0x3F)
        else:
            h = _bcd_to_int(d & 0x1F)
            if d & 0x20:
                h += 11  # Convert 12h to 24h
            elif h == 12:
                h = 0
            return h


    def _read_day(self):
        return _bcd_to_int(self._read(self._REG_DAY))


    def _read_date(self):
        return _bcd_to_int(self._read(self._REG_DATE))


    def _read_month(self):
        return _bcd_to_int(self._read(self._REG_MONTH))


    def _read_year(self):
        return _bcd_to_int(self._read(self._REG_YEAR))


    def read_all(self):
        """Return a tuple such as (year, month, date, day, hours, minutes,
        seconds).
        """
        return (self._read_year(), self._read_month(), self._read_date(),
                self._read_day(), self._read_hours(), self._read_minutes(),
                self._read_seconds())


    def read_str(self):
        """Return a string such as 'YY-DD-MMTHH-MM-SS'.
        """
        return '%02d-%02d-%02dT%02d:%02d:%02d' % (self._read_year(),
                self._read_month(), self._read_date(), self._read_hours(),
                self._read_minutes(), self._read_seconds())


    def read_datetime(self, century=21, tzinfo=None):
        """Return the datetime.datetime object.
        """
        return datetime((century - 1) * 100 + self._read_year(),
                self._read_month(), self._read_date(), self._read_hours(),
                self._read_minutes(), self._read_seconds(), 0, tzinfo=tzinfo)


def main():

    usbList = os.listdir('/media/pi')
    if len(usbList) == 0:
        print('No existe ningun USB conectado.')
        return 2

    usbDir = '/media/pi/' + usbList[0] + '/timer12C.txt'

    f = open(usbDir, 'w+')
    ds = DS1307(1, 0x68)

    try:
        while True:
            print(str(ds.read_datetime()))
            f.write(str(ds.read_datetime())+'\n')
            time.sleep(1)
    except KeyboardInterrupt:
        pass

    f.close()

if __name__ == "__main__":
    main()
