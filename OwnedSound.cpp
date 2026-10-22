#include "Common.h"
#include "OwnedSound.h"

OwnedSound::OwnedSound() :
    decoder(std::make_unique<ma_decoder>(ma_decoder())),
    sound(std::make_unique<ma_sound>(ma_sound()))
{
}

OwnedSound::OwnedSound(OwnedSound &&other) noexcept :
    data(std::move(other.data)),
    decoder(std::move(other.decoder)),
    sound(std::move(other.sound)),
    valid(other.valid)
{
    other.valid = false;
}

OwnedSound &OwnedSound::operator=(OwnedSound &&other) noexcept
{
    data = std::move(other.data);
    decoder = std::move(other.decoder);
    sound = std::move(other.sound);
    valid = other.valid;
    other.valid = false;
    return *this;
}

bool OwnedSound::loadFromMemory(ma_engine *engine, const void *src, size_t size)
{
    reset();
    data.assign(static_cast<const uint8_t *>(src), static_cast<const uint8_t *>(src) + size);
    return initFromOwnedData(engine);
}

bool OwnedSound::loadFromFile(ma_engine *engine, const char *path)
{
    reset();

    std::ifstream file(path, std::ios::binary | std::ios::ate);
    if (!file)
        return false;

    auto size = static_cast<size_t>(file.tellg());
    file.seekg(0);
    data.resize(size);
    if (!file.read(reinterpret_cast<char *>(data.data()), size))
        return false;

    return initFromOwnedData(engine);
}

void OwnedSound::reset()
{
    if (valid)
    {
        ma_sound_uninit(sound.get());
        ma_decoder_uninit(decoder.get());
        valid = false;
    }
    data.clear();
}

void OwnedSound::play(bool loop)
{
    if (valid)
    {
        ma_sound_start(sound.get());
        ma_sound_set_looping(sound.get(), loop ? MA_TRUE : MA_FALSE);
    }
}

bool OwnedSound::initFromOwnedData(ma_engine *engine)
{
    if (ma_decoder_init_memory(data.data(), data.size(), nullptr, decoder.get()) != MA_SUCCESS)
        return false;

    if (ma_sound_init_from_data_source(engine, decoder.get(), 0, nullptr, sound.get()) != MA_SUCCESS)
    {
        ma_decoder_uninit(decoder.get());
        return false;
    }

    valid = true;
    return true;
}
