
void main()
{
    // Pass vertex to fragment shader.
    // Convert from Model/Object space to Screen one.
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}

