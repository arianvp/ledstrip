import React, {Component} from 'react';

import GL from 'gl-react';
import {Surface} from 'gl-react-dom';


const shaders = (numLights) => GL.Shaders.create({
  helloGL: {
    frag: `
precision highp float;
varying vec2 uv;

const int numLights = ${numLights};

uniform vec2 resolution;
uniform float time;

float wd = 0.03;
vec3 hsv2rgb(vec3 c)
{
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

void main () {
  gl_FragColor = vec4(0.0, 0.0, 0.0, 0.5);

  vec2 uv2 = uv;
  uv2.y = (uv.y - 0.001) * resolution.y / resolution.x + 0.5;

  for (int i = 0; i < numLights; i++) {
    vec2 lightPos = vec2(float(i+1) / float(numLights +1), 0.5);
    vec2 dl = lightPos - uv2;
    float falloff = (wd * wd) / (dl.x * dl.x + dl.y * dl.y + wd * wd);
    gl_FragColor.xyz += hsv2rgb(vec3(sin(0.05*time - 0.5 * float(i)), 1.0, 1.0)) * falloff;
  }
  gl_FragColor.xyz = log(gl_FragColor.xyz + 1.0);
}
    `
  }
});

const lights = [
  [ 0.9, 0.9, 0.0],
  [ 0.9, 0.9, 0.0],
  [ 0.9, 0.9, 0.0],
  [ 0.9, 0.9, 0.0],
  [ 0.9, 0.9, 0.0],
  [ 0.9, 0.9, 0.0],
  [ 0.9, 0.9, 0.0],
];

class LLVMPreview extends React.Component {
  constructor (props) {
    super(props);
    this.state = {
      time: 0,
      width: 0,
      height: 0,
    };
  }
  componentDidMount () {
    const loop = time => {
      requestAnimationFrame(loop);
      this.setState({
        time : time / 1000.0,
      });
    };
    this.setState({width: this.hack.offsetWidth, height: this.hack.offsetHeight });
    window.addEventListener("resize", () => {
      this.setState({width: this.hack.offsetWidth, height: this.hack.offsetHeight });
    });

    requestAnimationFrame(loop);
  }
  render () {
    const { time, width, height} = this.state;
    return (
      <div style={{width: "100%", height: 150}} ref={(hack) => {this.hack = hack;}}>
        <Surface width={width} height={height}>
          <GL.Node
            shader={shaders(Math.floor(Math.sqrt(0.5 * width))).helloGL}
            uniforms={{ resolution: [width, height], time }}
          />
        </Surface>
      </div>
    );
  }
}

export default LLVMPreview;
