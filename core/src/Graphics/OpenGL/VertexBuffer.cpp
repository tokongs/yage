#include <VertexBuffer.h>

namespace yage
{
VertexBuffer::VertexBuffer(VertexBufferDesc desc, std::vector<Vertex> data)
{
    glCreateBuffers(1, &m_gl_object_id);
    bind();

    //calculate size of one vertex
    int size_of_vertex = 0;
    if (desc.has_position)
        size_of_vertex += 3 * sizeof(float);
    if (desc.has_normal)
        size_of_vertex += 3 * sizeof(float);
    if (desc.has_color)
        size_of_vertex += 3 * sizeof(float);
    if (desc.has_tex_coord)
        size_of_vertex += 2 * sizeof(float);
    if (desc.has_bones)
        size_of_vertex += 8 * sizeof(float);

    float *buffer = new float[size_of_vertex * data.size()];

    cleanData(desc, data, buffer);

    glBufferData(GL_ARRAY_BUFFER, sizeof(buffer), buffer, GL_STATIC_DRAW);
    unbind();

    if(desc.keep_shadow_buffer)
        m_shadow_copy = buffer;
    else
        delete[] buffer;
}

VertexBuffer::~VertexBuffer(){
    //Clean up loose pointers 
    if(m_buffer_desc.keep_shadow_buffer)
        delete[] m_shadow_copy;
        
    glDeleteBuffers(1, &m_gl_object_id);
}

void VertexBuffer::bind(){
    glBindBuffer(GL_ARRAY_BUFFER, m_gl_object_id);
}

void VertexBuffer::unbind(){
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::cleanData(VertexBufferDesc desc, std::vector<Vertex> data, float* result)
{
    int size_of_vertex = sizeof(result) / data.size();

    //fill the array with only populated values
    for (int i = 0; i < data.size(); i++)
    {
        int offset = 0;
        if (desc.has_position)
        {
            result[i * size_of_vertex + offset] = data[i].position.x;
            offset++;
            result[i * size_of_vertex + offset] = data[i].position.y;
            offset++;
            result[i * size_of_vertex + offset] = data[i].position.z;
            offset++;
        }
        if (desc.has_normal)
        {
            result[i * size_of_vertex + offset] = data[i].normal.x;
            offset++;
            result[i * size_of_vertex + offset] = data[i].normal.y;
            offset++;
            result[i * size_of_vertex + offset] = data[i].normal.z;
            offset++;
        }
        if (desc.has_color)
        {
            result[i * size_of_vertex + offset] = data[i].color.x;
            offset++;
            result[i * size_of_vertex + offset] = data[i].color.y;
            offset++;
            result[i * size_of_vertex + offset] = data[i].color.z;
            offset++;
        }
        if (desc.has_tex_coord)
        {
            result[i * size_of_vertex + offset] = data[i].tex_coord.x;
            offset++;
            result[i * size_of_vertex + offset] = data[i].tex_coord.y;
            offset++;
        }
        if (desc.has_bones)
        {
            result[i * size_of_vertex + offset] = (float)data[i].bone_id.x;
            offset++;
            result[i * size_of_vertex + offset] = (float)data[i].bone_id.y;
            offset++;
            result[i * size_of_vertex + offset] = (float)data[i].bone_id.z;
            offset++;
            result[i * size_of_vertex + offset] = (float)data[i].bone_id.w;
            offset++;
            result[i * size_of_vertex + offset] = data[i].bone_weight.x;
            offset++;
            result[i * size_of_vertex + offset] = data[i].bone_weight.y;
            offset++;
            result[i * size_of_vertex + offset] = data[i].bone_weight.z;
            offset++;
            result[i * size_of_vertex + offset] = data[i].bone_weight.w;
            offset++;
        }
    }
}
} // namespace yage