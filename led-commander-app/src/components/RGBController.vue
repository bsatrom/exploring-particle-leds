<template>
  <Page class="page">
    <ActionBar class="action-bar" title="RGB Commander">
    </ActionBar>

    <StackLayout class="rgb-main">
      <Label class="body" 
        textWrap=true 
        text="Adjust the sliders below to control the RGB LED of your device"/>

      <Slider id="redSlider" minValue="0" maxValue="255"
        v-model="redAmount" @valueChange="onRedChanged" />
      <Slider id="greenSlider" minValue="0" maxValue="255" 
        v-model="greenAmount" @valueChange="onGreenChanged" />
      <Slider id="blueSlider" minValue="0" maxValue="255" 
        v-model="blueAmount" @valueChange="onBlueChanged" />
      <GridLayout columns="100, 115" rows="80">
        <Label row="0" col="0"  text="Blink Speed" />
        <ListPicker row="0" col="1" :items="blinkSpeeds" 
          v-model="currentBlinkSpeed" @selectedIndexChange="onSpeedChanged" />
      </GridLayout>
      <GridLayout columns="100, 115" rows="80">
        <Label row="0" col="0"  text="Take Control" />
        <Switch row="0" col="1" id="controlRGBLED" 
          v-model="isControlling" @checkedChange="onControlChanged" />
      </GridLayout>
      <GridLayout columns="100, 115" rows="80">
        <Label row="0" col="0"  text="RAINBOWS!" />
        <Switch row="0" col="1" id="signaldevice" 
          v-model="isSignaling" @checkedChange="onSignalChanged" />
      </GridLayout>
    </StackLayout>

  </Page>
</template>

<script>
import axios from 'axios';

const baseUrl = 'https://api.particle.io/v1/devices/340020001147353138383138';
const token = '12345';

console.log(process.env);

const callParticleAPI = (endpoint, value, type = 'POST') => {
  axios({
    method: type,
    url: `${baseUrl}/${endpoint}?access_token=${token}`,
    data: `{ "arg": "${value}" }`,
    headers: { 'content-type': 'application/json' }
  }).catch(error => {
    console.error(error);
  });
};

export default {
  data() {
    return {
      blinkSpeeds: ['Slow', 'Normal', 'Fast'],
      currentBlinkSpeed: 0,
      redAmount: 80,
      blueAmount: 65,
      greenAmount: 44,
      isControlling: false,
      isSignaling: false
    };
  },
  methods: {
    onRedChanged: function(args) {
      callParticleAPI('setRed', this.redAmount);
    },
    onGreenChanged: function(args) {
      callParticleAPI('setGreen', this.greenAmount);
    },
    onBlueChanged: function(args) {
      callParticleAPI('setBlue', this.blueAmount);
    },
    onSpeedChanged: function(args) {
      callParticleAPI('setBlinkRate', this.currentBlinkSpeed);
    },
    onControlChanged: function(args) {
      callParticleAPI('toggleCtrl', this.isControlling);
    },
    onSignalChanged: function(args) {
      callParticleAPI('', this.isSignaling, 'PUT');
    }
  }
};
</script>

<style scoped>
.rgb-main {
  margin: 20;
}

Slider {
  margin: 10;
}

#redSlider {
  background-color: red;
}

#greenSlider {
  background-color: green;
}
</style>
