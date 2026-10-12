//
// Created by pierre on 10/12/26.
//
#include "gdt.hpp"

uint32_t GDT::SegmentDescriptor::get_limit() const {
    uint32_t limit_ = static_cast<uint32_t>(this->limit) + ((static_cast<uint32_t>(this->limit_and_flags) & 0b00001111) >> 4 << 16);
    return limit_;
}

uint32_t GDT::SegmentDescriptor::get_base() const {
    uint32_t base_ = static_cast<uint32_t>(this->base_low) | (static_cast<uint32_t>(this->base_mid) << 16) | (static_cast<uint32_t>(this->base_high) << 24);
    return base_;
}

uint8_t GDT::SegmentDescriptor::get_access() const {
    return access;
}

uint8_t GDT::SegmentDescriptor::get_flags() const {
    return (limit_and_flags & 0b11110000) >> 4;
}

void GDT::SegmentDescriptor::set_limit(uint32_t limit) {
    this->limit = limit & 0xffff;
    this->limit_and_flags = (limit_and_flags & 0b11110000) | (limit & 0b1111);
}

void GDT::SegmentDescriptor::set_base(uint32_t base) {
    this->base_low = base & 0xffff;
    this->base_mid = (base >> 16) & 0xffff;
    this->base_high = (base >> 24) & 0xffff;
}

void GDT::SegmentDescriptor::set_access(uint8_t access) {
    this->access = access;
}

void GDT::SegmentDescriptor::set_flags(uint8_t flags) {
    this->limit_and_flags = (limit_and_flags & 0b00001111) | (flags & 0b1111);
}
