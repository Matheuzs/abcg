#version 410

in vec3 fragN;
in vec3 fragL;
in vec3 fragV;
in vec2 fragTexCoord;
in vec3 fragPObj;
in vec3 fragNObj;

// Light properties
uniform vec4 Ia, Id, Is;

// Material properties
uniform vec4 Ka, Kd, Ks;
uniform float shininess;
uniform float timer;

// Diffuse texture sampler
uniform sampler2D diffuseTex;
uniform sampler2D complementaryTex;

uniform vec2 CloudRotationSpeed = vec2(0.01, 0.0);

out vec4 outColor;

// Blinn-Phong reflection model
vec4 BlinnPhong(vec3 N, vec3 L, vec3 V, vec2 texCoord) {
  N = normalize(N);
  L = normalize(L);

  // Compute lambertian term
  float lambertian = max(dot(N, L), 0.0);

  // Compute specular term
  float specular = 0.0;
  if (lambertian > 0.0) {
    V = normalize(V);
    vec3 H = normalize(L + V);
    float angle = max(dot(H, N), 0.0);
    specular = pow(angle, shininess);
  }

  vec4 map_Kd = texture(diffuseTex, texCoord);
  vec4 map_Ka = map_Kd;
  vec4 map_Kx = texture(complementaryTex, texCoord + (timer * CloudRotationSpeed));

  vec4 diffuseColor = map_Kd * Kd * Id * lambertian;
  vec4 specularColor = Ks * Is * specular;
  vec4 ambientColor = map_Ka * Ka * Ia;
  vec4 complementaryColor =  map_Kx;

  return ambientColor + diffuseColor + specularColor + complementaryColor * timer;
}

#define PI 3.14159265358979323846

// Spherical mapping
vec2 SphericalMapping(vec3 P) {
  float longitude = atan(P.x, P.z);
  float latitude = asin(P.y / length(P));

  float u = longitude / (2.0 * PI) + 0.5;  // From [-pi, pi] to [0, 1]
  float v = latitude / PI + 0.5;           // From [-pi/2, pi/2] to [0, 1]

  return vec2(u, v);
}

void main() {
  vec4 color;
  vec2 texCoord;

  texCoord = SphericalMapping(fragPObj);
  color = BlinnPhong(fragN, fragL, fragV, texCoord);

  if (gl_FrontFacing) {
    outColor = color;
  } else {
    float i = (color.r + color.g + color.b) / 3.0;
    outColor = vec4(i, 0, 0, 1.0);
  }
}
