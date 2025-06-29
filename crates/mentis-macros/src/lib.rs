use proc_macro::TokenStream;
use proc_macro2::Span;
use quote::quote;
use syn::parse_macro_input;
use syn::ItemFn;

extern crate proc_macro;

#[proc_macro_attribute]
pub fn Kernel(_attr: TokenStream, item: TokenStream) -> TokenStream {
    let func = parse_macro_input!(item as ItemFn);
    let func_ident_string = &func.sig.ident.to_string();
    let mut func_chars = func_ident_string.chars();
    let capitalized_func_name = match func_chars.next() {
        Some(first) => first.to_uppercase().collect::<String>() + func_chars.as_str(),
        None => String::new(),
    };
    let new_func_ident = syn::Ident::new(&capitalized_func_name, func.sig.ident.span());

    let expanded = quote! {
        #func

        pub struct #new_func_ident;

        impl #new_func_ident {
            pub fn source() -> &'static str {
                "kernel code"
            }
        }
    };
    expanded.into()
}
