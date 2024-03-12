## Tsunami Wave generation in Waves2Foam (OpenFOAM library)

# How to compile the code?

- Copy the `tsunamiWave_waveTheories/tsunamiWave` folder into `waves2Foam/src/waves2Foam/waveTheories/solitary/`

- Now copy the `tsunamiWaveProperties` folder into `waves2Foam/src/waves2FoamProcessing/preProcessing/setWaveProperties/solitary/`

- Add the line in `src/waves2Foam/Make/files` under `/* Solitary type */`
```
$(waveTheories)/$(solitary)/tsunamiWave/tsunamiWave.C
```
- Add the line in `waves2Foam/src/waves2FoamProcessing/Make/files` under `/* Solitary type */`
```
$(waveProp)/$(solitary)/tsunamiWaveProperties/tsunamiWaveProperties.C
```

- From the `waves2Foam` library location, compile the code using `Allwmake`

**FIN**
