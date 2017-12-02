#!/usr/bin/env python

# Author: MKozuch
# Date: 2017-12-20

import itertools

def checksum():
    checksum = 0
    
    while True:
        try:
            line = input()
        except EOFError:
            break
        if(not line):
            break
        else:
            try:
                lst = [ int(x) for x in line.split('\t')]
            except ValueError:
                checksum = -1
                break
            else:
                checksum += max(lst) - min(lst)
    print(checksum)

def evenly_divisible_checksum(): 
   checksum = 0
   
   while True:
      try:
         line = input()
      except EOFError:
         break
      if(not line):
         break
      else:
         try:
            lst = [ int(x) for x in line.split('\t')]
         except ValueError:
            checksum = -1
            break
         else:
            lst.sort()
            combinations = itertools.combinations(lst, 2)
            for x in combinations:
               try:
                  if not (x[1] % x[0]):
                     checksum += int(x[1] / x[0])
                     break
                  else:
                     continue
               except ZeroDivisionError:
                  checksum = -1
                  break
   print(checksum)


if __name__ == '__main__':
   #checksum();
   evenly_divisible_checksum();
