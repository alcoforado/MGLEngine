import Vue from "vue";

export default class RegisterComponents {
  static register() {
    const requireComponent = require.context(
      // The relative path of the components folder
      "./components",
      // Whether or not to look in subfolders
      true,
      // The regular expression used to match base component filenames
      /.*\.vue$/
    );

    requireComponent.keys().forEach(fileName => {
      // Get component config
      const componentConfig = requireComponent(fileName);
      // Get PascalCase name of component
      const componentName = fileName
        .split("/")
        .pop()
        .replace(/\.\w+$/, "");

      // Register component globally
      Vue.component(
        componentName,
        // Look for the component options on `.default`, which will
        // exist if the component was exported with `export default`,
        // otherwise fall back to module's root.
        componentConfig.default || componentConfig
      );
    });
  }
}
