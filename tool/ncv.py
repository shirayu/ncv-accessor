#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
"""
__author__ = 'Yuta Hayashibe' 
__version__ = ""
__copyright__ = ""
__license__ = "GPL v3"


import ncva
import logging
import math

class Ncv(object):
    def __init__(self, filename):
        assert isinstance(filename, unicode)
        
        filename_ncv = u"%s.0" % filename
        filename_ncv_utf8 = filename_ncv.encode("utf8")
        logging.info(u"Loading ncva(0) [%s].." % filename_ncv)
        self.__ncv = ncva.Ncva(filename_ncv_utf8)
        logging.info(u"Loaded ncva(0) [%s]" % filename_ncv)

        filename_vcn = u"%s.1" % filename
        filename_vcn_utf8 = filename_vcn.encode("utf8")
        logging.info(u"Loading ncva(1) [%s].." % filename_vcn)
        self.__vcn = ncva.Ncva(filename_vcn_utf8)
        logging.info(u"Loaded ncva(1) [%s]" % filename_vcn)

        self.__sum = self.__vcn.getTotal()

    def getScores(self, noun, case, verb):
        assert isinstance(noun, unicode)
        assert isinstance(case, unicode)
        assert isinstance(verb, unicode)
        
        ncvfreq_query = u"%s\t%s\t%s" % (noun, case, verb)
        ncvfreq = self.__ncv.get(ncvfreq_query.encode("utf8"))

        nfreq = self.__ncv.get(noun.encode("utf8"))

        vcfreq_query = u"%s\t%s" % (verb, case)
        vcfreq = self.__vcn.get(vcfreq_query.encode("utf8"))

        ncvfreq = float(ncvfreq)
        nfreq = float(nfreq)
        vcfreq = float(vcfreq)

        if ncvfreq == 0 or nfreq == 0 or vcfreq == 0:
            pmi = float("nan")
            log_likelifood = float("nan")
            wdice = float("nan")
        else:
            pmi = math.log(ncvfreq * self.__sum / nfreq / vcfreq)
            wdice = ( (2*ncvfreq) / (vcfreq + nfreq ) ) * ( math.log( ncvfreq, 2 )  ) ;

#            loglikelifood = 2 * [ (a+b+c+d+S) - (X+Y+Z+W)] <=それぞれ 頻度*log(頻度)としていること
#                                                        N   notN
#                                            CV	    a   b   X
#                                            notCV	c   d   Y
#                        Z   W   S(X+Y)
#            a+c=cvfreq          
#            a+b=nfreq

            a =  ncvfreq
            b =  nfreq - a
            c =  vcfreq - a
            d = self.__sum - a - b - c
            if ( (a == 0) or (b==0) or (c==0) or (d==0)
                    or (nfreq==0) or (vcfreq==0)):
                log_likelifood = 0
            else:
                a0 = math.log ( a , 2) * a;
                b0 = math.log ( b , 2) * b;
                c0 = math.log ( c , 2) * c;
                d0 = math.log ( d , 2) * d;

                X0 = math.log ( nfreq  ,2 ) * nfreq; #a+b
                Y0 = math.log ( c+d , 2 ) * (c+d); 
                Z0 = math.log ( vcfreq , 2) * vcfreq; #a+c
                W0 = math.log ( b+d , 2 ) * (b+d); 
                S0 = math.log ( self.__sum , 2) * self.__sum; 

                log_likelifood = 2 * ((a0 + b0 + c0 + d0 + S0) - (X0 + Y0 + Z0 + W0 ));

            out = u"%s\t%s\t%s\t%s\t%s\t%s\t%s" % (noun, case, verb, int(ncvfreq), pmi ,log_likelifood, wdice)
            print out.encode("utf8")


if __name__=='__main__':
    USAGE = """"""
    DESCRIPTION = """Inspect serialized file"""

    import optparse, sys
    oparser = optparse.OptionParser(usage=USAGE, description=DESCRIPTION)
    oparser.add_option('-i', dest = 'input_filename', help='')
    (opts, args) = oparser.parse_args()

    if opts.input_filename:
        import locale
        encoding = locale.getpreferredencoding()
        input_filename = unicode(opts.input_filename, encoding)

        ad = Ncv(input_filename)
#        ad.getScores(u"男", u"が", u"休む")
#        ad.getScores(u"警察", u"が", u"殺す")
#        ad.getScores(u"女", u"が", u"殺す")
#        ad.getScores(u"男", u"が", u"殺す")
#        ad.getScores(u"犯人", u"が", u"殺す")
#        ad.getScores(u"...", u"が", u"殺す")
#        ad.getScores(u"警察", u"が", u"逮捕する")

        in_encoding = sys.stdin.encoding
        if in_encoding is None:
            in_encoding = u"utf8"

        for line in iter(sys.stdin.readline, ""):
            line = unicode(line.rstrip(), in_encoding)
            items = line.split()
#            print items
            if len(items) == 3:
                ad.getScores(items[0], items[1], items[2])

