//
// Created by beiyu on 2020-12-06.
//

#include "dadecoder.h"
#include "daencoder.h"

int main(int argc, char *argv[]) {
    GisL::DaEncoder encoder;
    encoder.loadTextFile2Text("../data/Practise/practise_1/Decode2.txt");
    encoder.encode();
    encoder.writeBinaryFile("../data/Practise/practise_1/Ddddecode2.da");
    GisL::DaDecoder decoder;
    decoder.loadBinaryFile("../data/Practise/practise_1/Ddddecode2.da");
    decoder.decode();
    decoder.writeTextFile("../data/Practices/practise_1/Ddeeecode2.txt");
    return 1;
}
