#include <VertexBuffer.h>

namespace yage
{
DEFINE_LOGGERS(VertexBuffer);
VertexBuffer::VertexBuffer(VertexBufferDesc desc, std::vector<Vertex> data)
{
    INIT_LOGGERS(VertexBuffer);
    m_buffer_desc = desc;
    glCreateVertexArrays(1, &m_vao_object_id);
    LOG(VertexBuffer, info, "Created Vertex Array Object, ID: " + std::to_string(m_vao_object_id));

    bind();
    glCreateBuffers(1, &m_vb_object_id);
    glBindBuffer(GL_ARRAY_BUFFER, m_vb_object_id);
    LOG(VertexBuffer, info, "Created Vertex Buffer Object, ID: " + std::to_string(m_vb_object_id));

    //calculate size of one vertex
    int size_of_vertex = sizeOfVertex(desc);

    int buffer_size = size_of_vertex / sizeof(float) * data.size();
    float *buffer = new float[buffer_size];

    cleanData(desc, data, buffer);

    if (desc.keep_shadow_buffer)
        m_shadow_copy = std::vector<float>(buffer, buffer + buffer_size);

    glBufferData(GL_ARRAY_BUFFER, buffer_size * sizeof(float), buffer, GL_STATIC_DRAW);
    setupVao(desc);

    unbind();
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //Save a copy of the buffer to normal memory

    delete[] buffer;
}

VertexBuffer::~VertexBuffer()
{
    LOG(VertexBuffer, info, "Deleting Vertex Buffer Object, ID: " + std::to_string(m_vb_object_id));
    LOG(VertexBuffer, info, "Deleting Vertex Array Object, ID: " + std::to_string(m_vao_object_id));
    glDeleteBuffers(1, &m_vb_object_id);
    glDeleteVertexArrays(1, &m_vao_object_id);
}

void VertexBuffer::bind()
{
    glBindVertexArray(m_vao_object_id);
}

void VertexBuffer::unbind()
{
    glBindVertexArray(0);
}

void VertexBuffer::attachIndexBuffer(std::shared_ptr<IndexBuffer> index_buffer)
{
    LOG(VertexBuffer, info, "Attaching Index Buffer Object " +
         std::to_string(index_buffer->getGlId()) + " to Vertex Array Object " + std::to_string(m_vao_object_id));
    bool m_indexed = true;
    bind();
    index_buffer->bind();
    unbind();
    index_buffer->unbind();
}

void VertexBuffer::cleanData(VertexBufferDesc desc, std::vector<Vertex> data, float *result)
{
    int num_elements = sizeOfVertex(desc) / sizeof(float);

    //fill the array with only populated values
    for (int i = 0; i < data.size(); i++)
    {
        int offset = 0;
        if (desc.has_position)
        {
            result[i * num_elements + offset] = data[i].position.x;
            offset++;
            result[i * num_elements + offset] = data[i].position.y;
            offset++;
            result[i * num_elements + offset] = data[i].position.z;
            offset++;
        }
        if (desc.has_normal)
        {
            result[i * num_elements + offset] = data[i].normal.x;
            offset++;
            result[i * num_elements + offset] = data[i].normal.y;
            offset++;
            result[i * num_elements + offset] = data[i].normal.z;
            offset++;
        }
        if (desc.has_color)
        {
            result[i * num_elements + offset] = data[i].color.x;
            offset++;
            result[i * num_elements + offset] = data[i].color.y;
            offset++;
            result[i * num_elements + offset] = data[i].color.z;
            offset++;
        }
        if (desc.has_tex_coord)
        {
            result[i * num_elements + offset] = data[i].tex_coord.x;
            offset++;
            result[i * num_elements + offset] = data[i].tex_coord.y;
            offset++;
        }
        if (desc.has_bones)
        {
            result[i * num_elements + offset] = (float)data[i].bone_id.x;
            offset++;
            result[i * num_elements + offset] = (float)data[i].bone_id.y;
            offset++;
            result[i * num_elements + offset] = (float)data[i].bone_id.z;
            offset++;
            result[i * num_elements + offset] = (float)data[i].bone_id.w;
            offset++;
            result[i * num_elements + offset] = data[i].bone_weight.x;
            offset++;
            result[i * num_elements + offset] = data[i].bone_weight.y;
            offset++;
            result[i * num_elements + offset] = data[i].bone_weight.z;
            offset++;
            result[i * num_elements + offset] = data[i].bone_weight.w;
            offset++;
        }
    }
}

void VertexBuffer::setupVao(VertexBufferDesc desc)
{
    bind();

    int stride = sizeOfVertex(desc);
    int offset = 0;
    if (desc.has_position)
    {
        glEnableVertexAttribArray(POSITION_BUFFER_INDEX);
        glVertexAttribPointer(POSITION_BUFFER_INDEX, 3, GL_FLOAT, false, stride, (const void *)offset);
        offset = 3 * sizeof(float);
    }
    if (desc.has_normal)
    {
        glEnableVertexAttribArray(NORMAL_BUFFER_INDEX);
        glVertexAttribPointer(NORMAL_BUFFER_INDEX, 3, GL_FLOAT, false, stride, (const void *)offset);
        offset = 3 * sizeof(float);
    }
    if (desc.has_color)
    {
        glEnableVertexAttribArray(COLOR_BUFFER_INDEX);
        glVertexAttribPointer(COLOR_BUFFER_INDEX, 3, GL_FLOAT, false, stride, (const void *)offset);
        offset = 3 * sizeof(float);
    }
    if (desc.has_tex_coord)
    {
        glEnableVertexAttribArray(TEX_COORD_BUFFER_INDEX);
        glVertexAttribPointer(TEX_COORD_BUFFER_INDEX, 3, GL_FLOAT, false, stride, (const void *)offset);
        offset = 2 * sizeof(float);
    }
    if (desc.has_bones)
    {
        glEnableVertexAttribArray(BONE_ID_BUFFER_INDEX);
        glVertexAttribPointer(BONE_ID_BUFFER_INDEX, 3, GL_FLOAT, false, stride, (const void *)offset);
        offset = 4 * sizeof(float);
        glEnableVertexAttribArray(BONE_WEIGHT_BUFFER_INDEX);
        glVertexAttribPointer(BONE_WEIGHT_BUFFER_INDEX, 3, GL_FLOAT, false, stride, (const void *)offset);
        offset = 4 * sizeof(float);
    }
}

int VertexBuffer::sizeOfVertex(VertexBufferDesc desc)
{
    int size = 0;
    if (desc.has_position)
        size += 3 * sizeof(float);
    if (desc.has_normal)
        size += 3 * sizeof(float);
    if (desc.has_color)
        size += 3 * sizeof(float);
    if (desc.has_tex_coord)
        size += 2 * sizeof(float);
    if (desc.has_bones)
        size += 8 * sizeof(float);

    return size;
}

} // namespace yage
