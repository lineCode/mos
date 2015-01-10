#include "stream.hpp"

namespace mo {

Stream::Stream(const std::string file_name, const glm::vec3 position, const bool loop):
file_name(file_name), buffer_size(4096*8), loop(false), channels(1), playing(true) {
    vorbis_stream = stb_vorbis_open_filename((char*)file_name.c_str(), NULL, NULL);
    vorbis_info = stb_vorbis_get_info(vorbis_stream);
    samples_left = 	stb_vorbis_stream_length_in_samples(vorbis_stream) * vorbis_info.channels;

}

/*
Stream::Stream(const Stream & original)
    : file_name(original.file_name), position(original.position), loop(original.loop),
      buffer_size(original.buffer_size), channels(original.channels, playing(true))
{
    vorbis_stream = stb_vorbis_open_filename((char*)file_name.c_str(), NULL, NULL);
    vorbis_info = stb_vorbis_get_info(vorbis_stream);
    samples_left = 	stb_vorbis_stream_length_in_samples(vorbis_stream) * vorbis_info.channels;
}
*/

Stream::~Stream(){
    stb_vorbis_close(vorbis_stream);
}

StreamData Stream::read()
{
    StreamData sd;

    int  size = 0;
    int  result = 0;

    while(size < buffer_size){
        result = stb_vorbis_get_samples_short_interleaved(vorbis_stream, vorbis_info.channels, sd.samples+size, buffer_size-size);
        if(result > 0) size += result*vorbis_info.channels;
        else break;
    }

    if(size == 0) {
        sd.done = false;
        return sd;
    };

    samples_left -= size;

    sd.done = true;
    return sd;
}

}