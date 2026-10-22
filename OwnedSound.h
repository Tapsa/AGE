#pragma once
#include <vector>
#include <memory>
#include <miniaudio.h>

class OwnedSound
{
public:
    OwnedSound();
    OwnedSound(const OwnedSound &) = delete;
    OwnedSound(OwnedSound &&) noexcept;
    ~OwnedSound()
    {
        reset();
    }

    OwnedSound &operator=(const OwnedSound &) = delete;
    OwnedSound &operator=(OwnedSound &&) noexcept;

    bool loadFromMemory(ma_engine *engine, const void *src, size_t size);
    bool loadFromFile(ma_engine *engine, const char *path);
    void reset();
    void play(bool loop);

private:
    bool initFromOwnedData(ma_engine *engine);

    std::vector<uint8_t> data;
    std::unique_ptr<ma_decoder> decoder;
    std::unique_ptr<ma_sound> sound;
    bool valid = false;
};
