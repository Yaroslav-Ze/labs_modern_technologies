#include <iostream>
#include "barrel.hpp"


Barrel::Barrel(int v0, int zhid0, float spirt0) {
    if (v0 <= 0) {
        v = 0;
    }
    else {
        v = v0;
    }
    if (zhid0 >= v) {
        zhid = v;
    }
    else if (zhid0 <= 0) {
        zhid = 0;
    }
    else {
        zhid = zhid0;
    }
    if (spirt0 <= 0.) {
        spirt = 0;
    }
    else if (spirt0 >= 100.) {
        spirt = 100;
    }
    else {
        spirt = spirt0;
    }
}

float Barrel::get_spirt() {
    return spirt;
}

int Barrel::get_zhid() {
    return zhid;
}

int Barrel::get_v() {
    return v;
}

void Barrel::set_spirt(float s) {
    if (s <= 0.) {
        spirt = 0;
    }
    else if (s >= 100.) {
        spirt = 100.;
    }
    else {
        spirt = s;
    }
}

void Barrel::set_zhid(int zhid0) {
    if (zhid0 >= v) {
        zhid = v;
    }
    else if (zhid0 <= 0) {
        zhid = 0;
    }
    else {
        zhid = zhid0;
    }
}

void Barrel::set_v(int v0) {
    if (v0 <= 0) {
        v = 0;
    }
    else {
        v = v0;
    }
}

void Barrel::pereliv(Barrel &sth, int kryzhka) {
    float newgrad = ((sth.get_spirt()*sth.get_zhid()/100) + (kryzhka*this->get_spirt()/100)) * 100;
    this->set_zhid(this->get_zhid() - kryzhka);
    sth.set_zhid(sth.get_zhid() + kryzhka);
    sth.set_spirt(newgrad / sth.get_zhid());
    
}